# fingerprint-generator-cpp
Generates a picture based on a bunch of system information about a computer.

The same procedure that generates a picture based on information from a computer can eventually be used in a wrapper for ssh that will generate a picture using a host's public key as an input. Check the notes folder for interesting research on why this would be a better way of identifying a familiar host than a long string of characters

This started out as a way for me (Jake Mullins) to mess around with procedural generation in a low-level way with the libnoise library. I also did some practice with following specifications by programmatically creating a bitmap

Generates a picture using libnoise in the following configuration

┌──────────┐   ┌──────────┐
│          │   │          │
│ Generator├───► Modifier ├─┐
│          │   │          │ │   ┌──────────┐   ┌──────────┐
└──────────┘   └──────────┘ │   │          │   │          │
                            ├───► Combiner ├───► Modifier ├──┐
┌──────────┐   ┌──────────┐ │   │          │   │          │  │
│          │   │          │ │   └──────────┘   └──────────┘  │
│ Generator├───► Modifier ├─┘                                │
│          │   │          │                                  │    ┌──────────┐  ┌──────────┐  ┌──────────┐
└──────────┘   └──────────┘                                  │    │          │  │          │  │          │
                                                             ├────► Combiner ├──► Modifier ├──►  Output  │
┌──────────┐   ┌──────────┐                                  │    │          │  │          │  │          │
│          │   │          │                                  │    └──────────┘  └──────────┘  └──────────┘
│ Generator├───► Modifier ├─┐                                │
│          │   │          │ │   ┌──────────┐   ┌──────────┐  │
└──────────┘   └──────────┘ │   │          │   │          │  │
                            ├───► Combiner ├───► Modifier ├──┘
┌──────────┐   ┌──────────┐ │   │          │   │          │
│          │   │          │ │   └──────────┘   └──────────┘
│ Generator├───► Modifier ├─┘
│          │   │          │
└──────────┘   └──────────┘

Generator
    9 type choices
    All are necessary
    9 total
Modifier
    6 type choices
        Curve/Terrace is more than just input->output
    1 for not present
    7 total
Combiner
    4 type choices with only 2 inputs
    All are necessary
    4 total
Transformer
    4 type choices
    1 for not present
    5 total

All modules derive from noise::module::Module, 