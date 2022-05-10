# Genetic Algorithm

An implementation of a simple continuous genetic algorithm with C language.

## Installation


For the project to run, you need to have a C/C++ compiler installed.

The repository needs to be downloaded or cloned to a location accessible to you. To install it simply do the following from your terminal:

```bash
git clone https://github.com/haik-x/geneticAlgorithm.git
```

## Assumptions for the species

* Species do not harm each other.
* Food is a limited resource and it expires.
* The bigger the particles, the greater the variety of food they can eat. (The species can only eat food that is not too big with respect to their size).
* Speed and visibility are positive attributes for the species. The greater their vision, the bigger the area they can cover, and the faster they are, the sooner they can get to the food.
* The species will try to eat the food which is nearest to it and within their range of vision. 
* Species can only reproduce when a generation ends and they have eaten more than once. 
* Surviving species can go through small mutations after each generation.  


## Contributing
There's a lot that can be improved, pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
