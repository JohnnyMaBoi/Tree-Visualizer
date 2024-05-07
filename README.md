# Required packages

This repository requires the GraphViz, Curl, and LibXml2 libraries. They can all be installed with sudo apt-get, but graphviz may not work on the default branch for all systems:

sudo apt-get install graphviz OR sudo apt-get install graphviz-dev

# Usage

All files created at runtime are located in the current working directory.

The graph_builder executable generates a .dot file that can be used with graphviz to generate a circular "twopi" graph. For examples of these graphs, see the graphviz documentation page [twopi graphviz examples page](https://graphviz.org/Gallery/twopi/). The link_extractor executable uses a hardcoded title of a wikipedia page to call the API for all links outgoing from the origin article and save a JSON file of that response.

To turn the dot framework into a png, use the following terminal command in the directory of the generated dot file:

twopi -Tpng graph.dot -o graph.png
