#include "Event.h"

// clang-format off
static js::Event playerAnimationChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_ANIMATION_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeAnimationEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldAnimDict", e->GetOldAnimationDict());
    args.Set("newAnimDict", e->GetNewAnimationDict());
    args.Set("oldAnimName", e->GetOldAnimationName());
    args.Set("newAnimName", e->GetNewAnimationName());
});

static js::Event playerVehicleEnteredEvent(alt::CEvent::Type::PLAYER_ENTER_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerStartVehicleEnterEvent(alt::CEvent::Type::PLAYER_ENTERING_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerEnteringVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerVehicleLeftEvent(alt::CEvent::Type::PLAYER_LEAVE_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerVehicleSeatChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeVehicleSeatEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("oldSeat", e->GetOldSeat());
    args.Set("newSeat", e->GetNewSeat());
});

static js::Event playerStartTalkingEvent(alt::CEvent::Type::PLAYER_START_TALKING, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerStartTalkingEvent*>(ev);

    args.Set("player", e->GetPlayer());
});

static js::Event playerStopTalkingEvent(alt::CEvent::Type::PLAYER_STOP_TALKING, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerStopTalkingEvent*>(ev);

    args.Set("player", e->GetPlayer());
});

static js::Event playerInteriorChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_INTERIOR_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeInteriorEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldInterior", e->GetOldInteriorLocation());
    args.Set("newInterior", e->GetNewInteriorLocation());
});

static js::Event playerDimensionChangeEvent(alt::CEvent::Type::PLAYER_DIMENSION_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerDimensionChangeEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldDimension", e->GetOldDimension());
    args.Set("newDimension", e->GetNewDimension());
});
