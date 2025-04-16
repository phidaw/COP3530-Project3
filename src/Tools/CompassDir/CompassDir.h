#pragma once

struct CompassDir
{
    enum Ordinal { NW, NE, SW, SE };
    enum Cardinal { North, East, South, West, center };
};

typedef CompassDir::Cardinal Cardinal;
typedef CompassDir::Ordinal Ordinal;