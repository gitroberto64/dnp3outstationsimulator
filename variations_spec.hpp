#pragma once
#include <cstdint>
#include <map>

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
     g20v1,
     g20v2,
     g20v5,
     g20v6,
     g22v1,
     g22v2,
     g22v5,
     g22v6,
     g21v1,
     g21v2,
     g21v5,
     g21v6,
     g21v9,
     g21v10,
     g23v1,
     g23v2,     
     g23v5,
     g23v6,
     g10v2,
     g11v1,
     g11v2,
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

const std::map<Variations, std::string> variations_spec =
{
    { Variations::g1v1 ,"pack " }
};
