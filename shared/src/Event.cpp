#include "Event.h"
#include "interfaces/IResource.h"
#include "magic_enum/include/magic_enum.hpp"

extern js::Class eventContextClass, cancellableEventContextClass;

std::optional<js::Promise> js::Event::CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource)
{
    js::Function onEvent = resource->GetBindingExport<v8::Function>(BindingExport::ON_EVENT);
    if (!onEvent.IsValid())
        return std::nullopt;

    std::optional<v8::Local<v8::Value>> result = onEvent.Call<v8::Local<v8::Value>>(custom, type, args.Get());
    auto promise = js::Promise{ result.value_or(v8::Local<v8::Value>()).As<v8::Promise>() };

    if (!promise.Get().IsEmpty())
        return promise;

    return std::nullopt;
}

void js::Event::SendEvent(const alt::CEvent* ev, IResource* resource)
{
    Event* eventHandler = GetEventHandler(ev->GetType());
    if(!eventHandler) return;

    EventArgs eventArgs;
    if(ev->IsCancellable())
        eventArgs = cancellableEventContextClass.Create(resource->GetContext(), (void*)ev);
    else
        eventArgs = eventContextClass.Create(resource->GetContext(), (void*)ev);

    eventHandler->argsCb(ev, eventArgs);

    auto promise = CallEventBinding(false, (int)ev->GetType(), eventArgs, resource);
    if (promise.has_value() && ev->GetType() == alt::CEvent::Type::RESOURCE_STOP && resource->GetResource() == static_cast<const alt::CResourceStopEvent*>(ev)->GetResource())
    {
        promise->Await();
    }

    eventArgs.Get()->SetAlignedPointerInInternalField(1, nullptr);
}

void js::Event::SendEvent(EventType type, EventArgs& args, IResource* resource)
{
    CallEventBinding(true, (int)type, args, resource);
}

// Class
static void CancelEventCallback(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CCancellableEvent* ev = ctx.GetExtraInternalFieldValue<alt::CCancellableEvent>();
    if(ev->WasCancelled()) return;
    ev->Cancel();
}
static void IsCancelledGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CCancellableEvent* ev = ctx.GetExtraInternalFieldValue<alt::CCancellableEvent>();
    ctx.Return(ev->WasCancelled());
}
static void TypeGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CEvent* ev = ctx.GetExtraInternalFieldValue<alt::CEvent>();
    ctx.Return(ev->GetType());
}

static void IsCancellableGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CEvent* ev = ctx.GetExtraInternalFieldValue<alt::CEvent>();
    ctx.Return(ev->IsCancellable());
}

// clang-format off
extern js::Class eventContextClass("EventContext", [](js::ClassTemplate& tpl) {
    tpl.LazyProperty("type", TypeGetter);
    tpl.LazyProperty("isCancellable", IsCancellableGetter);
}, true);

extern class js::Class cancellableEventContextClass("CancellableEventContext", &eventContextClass, [](js::ClassTemplate& tpl) {
    tpl.BoundMethod("cancel", CancelEventCallback);
    tpl.Property("isCancelled", IsCancelledGetter);
}, true);
