// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = atoi(&fraction[0]);
    int y = atoi(&fraction[2]);

    return (x * 8 / y);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int len = strlen(note);     // defining notation : XY or XYZ
    int octave = atoi(&note[len] - 1); //store octave
    char natural_note = (note[0]);   //store only natural note.
    float freq = 0;
    char alter = 0;

    if (len == 3) // if it's a altered note , I take the value.
    {
        alter = note[len - 2];
    }

    //cheking octave
    if (octave > 4)  // base note A4 == 440 Hz
    {
        freq = 440 * pow(2, octave - 4);
    }
    if (octave < 4)
    {
        freq = 440 / pow(2, 4 - octave);
    }
    if (octave == 4)
    {
        freq = 440;
    }

    // checking the note
    switch (natural_note)
    {
        case 'B' :
            freq = freq * (pow(2, 2.0 / 12));
            break;
        case 'C' :
            freq = freq / (pow(2, 9.0 / 12)) ;
            break;
        case 'D' :
            freq = freq / (pow(2, 7.0 / 12));
            break;
        case 'E' :
            freq = freq / (pow(2, 5.0 / 12))  ;
            break;
        case 'F' :
            freq = freq / (pow(2, 4.0 / 12)) ;
            break;
        case 'G' :
            freq = freq / (pow(2, 2.0 / 12))  ;
            break;
    }

    // checking if it's altered.
    if (alter != 0)
    {
        if (alter == '#')
        {
            freq = (pow(2, 1.0 / 12)) * freq ;
        }
        else // It's b
        {
            freq = freq / (pow(2, 1.0 / 12));
        }
    }
    return round(freq);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0') // '\0' : Void string
    {
        return true;
    }
    else
    {
        return false;
    }
}
