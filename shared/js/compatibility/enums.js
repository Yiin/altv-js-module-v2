/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

for (const enumName in alt.Enums) {
    cppBindings.registerCompatibilityExport(enumName, alt.Enums[enumName]);
}
