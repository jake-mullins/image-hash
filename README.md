# fingerprint-generator-cpp
Generates a picture based on a bunch of system information about a computer.

The same procedure that generates a picture based on information from a computer can eventually be used in a wrapper for ssh that will generate a picture using a host's public key as an input. Check the notes folder for interesting research on why this would be a better way of identifying a familiar host than a long string of characters

This started out as a way for me (Jake Mullins) to mess around with procedural generation in a low-level way with the libnoise library. I also did some practice with following specifications by programmatically creating a bitmap

To compile, follow these steps
    
```shell
cd
git clone https://github.com/qknight/libnoise.git
cd libnoise
mkdir build
cd build
cmake ..
make
sudo make install
cd ~/image-hash
g++ main.cpp -o image-hash -lnoise
```

Generates a picture using libnoise in the following configuration
## The diagram below formats correctly when cloned or when looking at the raw data representation of this file
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

Number of classes per module type:
- Generator: 9/9 classes
- Combiner: 4/4 classes
- Transformer: 4/5 classes
- Modifier: 6/7 classes
   
## Possible to-do
Probably could make a recursive function for the generators
