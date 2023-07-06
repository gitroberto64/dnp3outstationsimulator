#pragma once
#include <cstdint>
#include <map>
#include <opendnp3/outstation/OutstationConfig.h>

enum class Variations : std::uint16_t
{
    g1v1,
    g1v2,
    g2v1,
    g2v2,
    g2v3,
    g3v2,
    g4v1,
    g4v2,
    g4v3,
    g10v2,
    g11v1,
    g11v2,
    g20v1,
    g20v2,
    g20v5,
    g20v6,
    g21v1,
    g21v2,
    g21v5,
    g21v6,
    g21v9,
    g21v10,
    g22v1,
    g22v2,
    g22v5,
    g22v6,
    g23v1,
    g23v2,     
    g23v5,
    g23v6,
    g30v1,
    g30v2,
    g30v3,
    g30v4,
    g30v5,
    g30v6,
    g32v1,
    g32v2,
    g32v3,
    g32v4,
    g32v5,
    g32v6,
    g32v7,
    g32v8,
    g40v1,
    g40v2,
    g40v3,
    g40v4,
    g42v1,
    g42v2,
    g42v3,
    g42v4,
    g42v5,
    g42v6,
    g42v7,
    g42v8  
};

struct VarSpec
{
    std::string name;
    std::string description;
};

const std::map<Variations, VarSpec> variations_spec =
{
    { Variations::g1v1,   { opendnp3::StaticBinaryVariationSpec::to_string(opendnp3::StaticBinaryVariation::Group1Var1)                         , "Packed format" } },
    { Variations::g1v2,   { opendnp3::StaticBinaryVariationSpec::to_string(opendnp3::StaticBinaryVariation::Group1Var2)                         , "With flags" } },
    { Variations::g2v1,   { opendnp3::EventBinaryVariationSpec::to_string(opendnp3::EventBinaryVariation::Group2Var1)                           , "Without time" } },
    { Variations::g2v2,   { opendnp3::EventBinaryVariationSpec::to_string(opendnp3::EventBinaryVariation::Group2Var2)                           , "With absolute time" } },
    { Variations::g2v3,   { opendnp3::EventBinaryVariationSpec::to_string(opendnp3::EventBinaryVariation::Group2Var3)                           , "With relative time" } },
    { Variations::g3v2,   { opendnp3::StaticDoubleBinaryVariationSpec::to_string(opendnp3::StaticDoubleBinaryVariation::Group3Var2)             , "With flags" } },
    { Variations::g4v1,   { opendnp3::EventDoubleBinaryVariationSpec::to_string(opendnp3::EventDoubleBinaryVariation::Group4Var1)               , "Without time" } },
    { Variations::g4v2,   { opendnp3::EventDoubleBinaryVariationSpec::to_string(opendnp3::EventDoubleBinaryVariation::Group4Var2)               , "With absolute time" } },
    { Variations::g4v3,   { opendnp3::EventDoubleBinaryVariationSpec::to_string(opendnp3::EventDoubleBinaryVariation::Group4Var3)               , "With relative time" } },
    { Variations::g10v2,  { opendnp3::StaticBinaryOutputStatusVariationSpec::to_string(opendnp3::StaticBinaryOutputStatusVariation::Group10Var2), "Output status with flags" } },
    { Variations::g11v1,  { opendnp3::EventBinaryOutputStatusVariationSpec::to_string(opendnp3::EventBinaryOutputStatusVariation::Group11Var1)  , "Status without time" } },
    { Variations::g11v2,  { opendnp3::EventBinaryOutputStatusVariationSpec::to_string(opendnp3::EventBinaryOutputStatusVariation::Group11Var2)  , "Status with time" } },
    { Variations::g20v1,  { opendnp3::StaticCounterVariationSpec::to_string(opendnp3::StaticCounterVariation::Group20Var1)                      , "32-bit with flag" } },
    { Variations::g20v2,  { opendnp3::StaticCounterVariationSpec::to_string(opendnp3::StaticCounterVariation::Group20Var2)                      , "16-bit with flag" } },
    { Variations::g20v5,  { opendnp3::StaticCounterVariationSpec::to_string(opendnp3::StaticCounterVariation::Group20Var5)                      , "32-bit without flag" } },
    { Variations::g20v6,  { opendnp3::StaticCounterVariationSpec::to_string(opendnp3::StaticCounterVariation::Group20Var6)                      , "16-bit without flag" } },
    { Variations::g21v1,  { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var1)          , "32-bit with flag" } },
    { Variations::g21v2,  { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var2)          , "16 bit with flag" } },
    { Variations::g21v5,  { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var5)          , "32-bit with flag and time" } },
    { Variations::g21v6,  { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var6)          , "16-bit with flag and time" } },
    { Variations::g21v9,  { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var9)          , "32-bit without flag" } },
    { Variations::g21v10, { opendnp3::StaticFrozenCounterVariationSpec::to_string(opendnp3::StaticFrozenCounterVariation::Group21Var10)         , "16-bit without flag" } },
    { Variations::g22v1,  { opendnp3::EventCounterVariationSpec::to_string(opendnp3::EventCounterVariation::Group22Var1)                        , "32-bit with flag" } },
    { Variations::g22v2,  { opendnp3::EventCounterVariationSpec::to_string(opendnp3::EventCounterVariation::Group22Var2)                        , "16-bit with flag" } },
    { Variations::g22v5,  { opendnp3::EventCounterVariationSpec::to_string(opendnp3::EventCounterVariation::Group22Var5)                        , "32-bit with flag and time" } },
    { Variations::g22v6,  { opendnp3::EventCounterVariationSpec::to_string(opendnp3::EventCounterVariation::Group22Var6)                        , "16-bit with flag and time" } },
    { Variations::g23v1,  { opendnp3::EventFrozenCounterVariationSpec::to_string(opendnp3::EventFrozenCounterVariation::Group23Var1)            , "32-bit with flag" } },
    { Variations::g23v2,  { opendnp3::EventFrozenCounterVariationSpec::to_string(opendnp3::EventFrozenCounterVariation::Group23Var2)            , "16-bit with flag" } },
    { Variations::g23v5,  { opendnp3::EventFrozenCounterVariationSpec::to_string(opendnp3::EventFrozenCounterVariation::Group23Var5)            , "32-bit with flag and time" } },
    { Variations::g23v6,  { opendnp3::EventFrozenCounterVariationSpec::to_string(opendnp3::EventFrozenCounterVariation::Group23Var6)            , "16-bit with flag and time" } },
    { Variations::g30v1,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var1)                        , "32-bit with flag" } },
    { Variations::g30v2,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var2)                        , "16-bit with flag" } },
    { Variations::g30v3,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var3)                        , "32-bit without flag" } },
    { Variations::g30v4,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var4)                        , "16-bit without flag" } },
    { Variations::g30v5,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var5)                        , "Single-prec flt-pt with flag" } },
    { Variations::g30v6,  { opendnp3::StaticAnalogVariationSpec::to_string(opendnp3::StaticAnalogVariation::Group30Var6)                        , "Double-prec flt-pt with flag" } },
    { Variations::g32v1,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var1)                          , "32-bit without time" } },
    { Variations::g32v2,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var2)                          , "16-bit without time" } },
    { Variations::g32v3,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var3)                          , "32-bit with time" } },
    { Variations::g32v4,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var4)                          , "16-bit with time" } },
    { Variations::g32v5,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var5)                          , "Single-prec flt-pt without time" } },
    { Variations::g32v6,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var6)                          , "Double-prec flt-pt without time" } },
    { Variations::g32v7,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var7)                          , "Single-prec flt-pt with time" } },
    { Variations::g32v8,  { opendnp3::EventAnalogVariationSpec::to_string(opendnp3::EventAnalogVariation::Group32Var8)                          , "Double-prec flt-pt with time" } },
    { Variations::g40v1,  { opendnp3::StaticAnalogOutputStatusVariationSpec::to_string(opendnp3::StaticAnalogOutputStatusVariation::Group40Var1), "32-bit with flag" } },
    { Variations::g40v2,  { opendnp3::StaticAnalogOutputStatusVariationSpec::to_string(opendnp3::StaticAnalogOutputStatusVariation::Group40Var2), "16-bit with flag" } },
    { Variations::g40v3,  { opendnp3::StaticAnalogOutputStatusVariationSpec::to_string(opendnp3::StaticAnalogOutputStatusVariation::Group40Var3), "Single-prec flt-pt with flag" } },
    { Variations::g40v4,  { opendnp3::StaticAnalogOutputStatusVariationSpec::to_string(opendnp3::StaticAnalogOutputStatusVariation::Group40Var4), "Double-prec flt-pt with flag" } },
    { Variations::g42v1,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var1)  , "32-bit without time" } },
    { Variations::g42v2,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var2)  , "16-bit without time" } },
    { Variations::g42v3,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var3)  , "32-bit with time" } },
    { Variations::g42v4,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var4)  , "16-bit with time" } },
    { Variations::g42v5,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var5)  , "Single-prec flt-pt without time" } },
    { Variations::g42v6,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var6)  , "Double-prec flt-pt without time" } },
    { Variations::g42v7,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var7)  , "Single-prec flt-pt with time" } },
    { Variations::g42v8,  { opendnp3::EventAnalogOutputStatusVariationSpec::to_string(opendnp3::EventAnalogOutputStatusVariation::Group42Var8)  , "Double-prec flt-pt with time" } }
}; 
 
std::string description_and_name(Variations var)
{
    return variations_spec.at(var).description + " (" + variations_spec.at(var).name + ')';
}