# Genetic Algorithm

An implementation of a simple continuous genetic algorithm with C language.


![2022-05-11 14 23 35](https://user-images.githubusercontent.com/53795904/167929758-4779f14f-ad22-4b51-926e-46c2e36a8f16.gif)

> “One general law, leading to the advancement of all organic beings, namely, multiply, vary, let the strongest live and the weakest die.”
― Charles Darwin, The Origin of Species


This genetic algorithm implementation explores simulating the process of evolution in an ecosystem of non-intelligent and instict-based beings. The objects that move about the screen meet each other, reproduce asexually, and pass their genes on to a new generation. The previous ensures the continuation of fittest of all beings and their evolution.


## Installation


For the project to run, you need to have a C/C++ compiler installed.

The repository needs to be downloaded or cloned to a location accessible to you. To install it simply do the following from your terminal:

```bash
git clone https://github.com/haik-x/geneticAlgorithm.git
```

## Assumptions

* Species do not harm each other.
* Food is a limited resource and it expires.
* The bigger the particles, the greater the variety of food they can eat. (The species can only eat food that is not too big with respect to their size).
* Speed and visibility are positive attributes for the species. The greater their vision, the bigger the area they can cover, and the faster they are, the sooner they can get to the food.
* The species will try to eat the food which is nearest to it and within their range of vision. 
* Species can only reproduce when a generation ends and they have eaten more than once. 
* Surviving species can go through small mutations after each generation.  


## Contributing
There's a lot that can be improved, pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
