# Gradient Method for the Minimization of a multivariate function

###  README for the 1st Challenge of the PACS course

This program allows the user to find the minimum point of a function passed through a data.json file. 
The minimum point is computed using the gradient method. The gradient of the function can be computed either by extracting the exact gradient from data.json or by using an approximation through centered differences; the choice is up to the user.  

The file is divided into :
- src 
- include
- data.json
- Makefile
- README
- LICENSE
- .gitignore  


how to configure and how to run the code smoothly, what to change, ............................
To run the code, you need to make some changes to the Makefile:
- in CPPFLAGS, substitute -I../pacs-examples/Examples/include/muparserx -I../pacs-examples/Examples/include with the paths to json.hpp and to muparserx
- in LDFLAGS, substitute -L../pacs-examples/Examples/lib with the path to your libraries' directory in order to allow the linking phase

...........................