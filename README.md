# fingerprint-generator-cpp
Generates an image based on an input string.

When you ssh onto a host, especially if from a new computer, you often get complaints that the host's public key has changed. Most of the time, this is for legitimate reasons, and a user will mindlessly type ```yes```. This makes most people vulnerable to MITM attacks, exposing plaintext passwords. In addition, humans are provably bad at 2 things:
1. Remember secure passwords
2. Compare meaningless or random strings
Meaning that even if a public key were to change when it wasn't supposed to, signifying an MITM attack, most users wouldn't notice. Attaching an image could help defend against this by leveraging human's ability to recognize shapes and colors to minimize the risk of accepting an ssh session that is victim to an MITM.

Other use cases include displaying a visual representation of a (browser fingerprint)[https://coveryourtracks.eff.org/static/browser-uniqueness.pdf], which can streamline the process of making sure your browser is not identifiable by a server.

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
