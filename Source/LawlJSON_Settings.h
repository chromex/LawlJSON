#ifndef LAWLJSON_SETTINGS_H
#define LAWLJSON_SETTINGS_H

#define LJ_NUMBER_TYPE double

// Set to one if you want LawlJSON to be inside the LawlJSON namespace
// and 0 if not.
//
#if 1
    #define BEGIN_LAWLJSON namespace LawlJSON {
    #define END_LAWLJSON }
#else
    #define BEGIN_LAWLJSON
    #define END_LAWLJSON
#endif

#endif