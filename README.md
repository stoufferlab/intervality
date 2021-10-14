## intervality

This package implements in C++ the functions needed to order diet items in a predator-prey food web such that all diets are maximally contiguous
(Stouffer et al. 2006), or determine the contiguity when diet items are ordered based on some known quantity (e.g., mass; Stouffer et al. 2011). As input, both methods require a file listing all predator-prey interactions, and the second requires a paired list of species and their trait value to order on. Full details of the algorithm are available at:

DB Stouffer, J Camacho, LAN Amaral. A robust measure of food web intervality. *Proceedings of the National Academy of Sciences USA* 103(50), 19015–19020 (2006). http://dx.doi.org/10.1073/pnas.0603844103

DB Stouffer, EL Rezende, LAN Amaral. The role of body mass in diet contiguity and food-web structure. *Journal of Animal Ecology* 80(3), 632–639 (2011). http://dx.doi.org/10.1111/j.1365-2656.2011.01812.x

## Build instructions
After cloning the repository, you can build the executables by running:

    sudo apt-get install autoconf libtool
    autoreconf --install
    ./configure
    make

This produces:

* `src/minimumIntervality`. This executable uses simulated annealing to determine the minimum possible number of gaps (aka intervality).

* `src/massIntervality`. This executable orders diet items based on specified values and returns the corresponding intervality.

You can view the options of any of these scripts with the `--help` flag.

## Usage

To compute the minimum intervality of an interaction matrix, users should run the `minimumIntervality` executable
with something like this:

```sh
./src/minimumIntervality -f path/to/net.dat
```

where `path/to/net.dat` is a text file that stores the interaction information. By default, `minimumIntervality` assumes that the interactions will be in a
format similar to [data/net.dat](data/net.dat), and that the first column corresponds to integer labels for predators and the second column to integer labels for prey.

To compute the intervality of an interaction matrix when ordering diets by a pre-defined measure, users should run the `massIntervality` executable
with something like this:

```sh
./src/massIntervality -f path/to/net.dat -m path/to/masses.dat
```

where `path/to/net.dat` is a text file that stores the interaction information. By default, `massIntervality` assumes that the interactions will be in a
format similar to [data/net.dat](data/net.dat), and that the first column corresponds to integer labels for predators and the second column to integer labels for prey. It also assumes that all species will be provided a corresponding mass/trait in a format similar to [data/masses.dat](data/masses.dat), and that the first column corresponds to the species' unique integer label and the second column to the continuous valued trait.
