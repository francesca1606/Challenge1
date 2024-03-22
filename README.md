# Gradient Method for the Minimization of a multivariate function

##  README for the 1st Challenge of the PACS course

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
<br/><br/><br/>
To run the code, you need to make some changes to the Makefile:
- in CPPFLAGS, substitute -I../pacs-examples/Examples/include/muparserx -I../pacs-examples/Examples/include with the paths to json.hpp and to muparserx

          CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -Ipath/to/muparserx -Ipath/to/json.hpp

- in LDFLAGS, substitute -L../pacs-examples/Examples/lib with the path to your libraries' directory in order to allow the linking phase

          LDFLAGS ?= -Lpath/to/libmuparserx.a         ??è quella giusta????????


After having done these steps, simply run make in the terminal
If you want to remove the object file and the executable, run make clean


-----------------


## User's choices and changes ###

You can change the parameters inside data.json to modify the parameters and the function to minimize.

data.json contains:
- the starting point x0
- the initial step alpha0
- the gradients' residual tolerance tol_res
- the points' residual tolerance tol_x
- the maximum number of iterations max_iter
- parameter mu, used to update the step length using exponential or inverse decay method
- parameter sigma, used to update the step length using the line search method
- the function to minimize f
- the exact gradient df
- the number of variables dim

<br/><br/>
**Warnings**

As variables' names use x followed by a number >= 1

sigma assumes values in (0, 0.5)

x0 must be a vector of dimension dim; f is a dim-dimensional function; df is a dim_dimensional vector of dim-dimensional variables
<br/><br/> <br/><br/>
For the minimization, you can choose to employ the exact gradient, passed through data.json, and an approximated gradient (centered scheme). To do so, when the program asks you, type in the terminal either   

exact   

or    

finite differences

In the case of finite differences, you can also modify the value of epsilon (the default is 1e-6).
<br/><br/><br/>
In gradient_method() function inside main.cpp, you may want to change the method used to update the step length att each iteration. To do so, you can modify this line:
> constexpr strategies strat=strategies::exponential_decay;

changing exponential_decay with inverse_decay or Armijo_rule


// CAMBIA, PUò ESSERE UTILE  !!!!!!!
//The user may choose between reading the exact gradient from the provided data.json file
//or the computation of an approximated gradient through finite differences