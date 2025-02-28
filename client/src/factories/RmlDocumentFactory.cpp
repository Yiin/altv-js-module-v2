#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler rmlDocumentFactory(alt::IBaseObject::Type::RML_DOCUMENT, [](js::Object& args) -> alt::IBaseObject* {
    alt::IRmlDocument::CreateOptions options;

    if(!args.Get("url", options.url)) return nullptr;
    
    options.isFullscreen = args.Get<bool>("isFullscreen", options.isFullscreen);
    options.size = args.Get<alt::Vector2i>("size", options.size);

    js::IResource* resource = args.GetResource();
    options.currentPath = js::SourceLocation::GetCurrent(resource).file;

    return alt::ICore::Instance().CreateDocument(options, resource->GetResource());
});
