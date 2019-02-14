### Resources
To contribute, considers the [issues](https://github.com/AndreaIdini/Schroedinger/issues) and the [to-do](https://github.com/AndreaIdini/Schroedinger/projects) lists. 
Watch the introduction video [video \(IT\)](https://www.youtube.com/watch?v=KH8xd0TKkz4)
and contact [Andrea Idini](mailto:andrea.idini@gmail.com).
Priviledge channel for contributions is the telegram group [@scienza](https://t.me/Scienza).

### Styling guide
This is based on the [Google C++ Styling guide](https://google.github.io/styleguide/cppguide.html), here's the most important things:

- Use `.cpp` (**NOT** `.cc`) as extension for C++ files and `.h` for headers files
- every `.cpp` file should have an associated `.h` file
- Use [header guards](https://en.wikipedia.org/wiki/Include_guard) ( `#pragma once` ([rel](https://en.wikipedia.org/wiki/Pragma_once)) can be used, but header guards are preferred)
- Use Forward Declarations (declare functions without defininf them, basically using the header)
- Prefer small and focused functions
- Use inline function for 8 lines long functions or less
- Do not define implicit conversions. Use the explicit keyword
- Use a struct only for passive objects that carry data; everything else is a class.
- Declare variables in a local way whenever is possible (best prefix for a global variable is `//`)
- Initialize variables when declaring them
- Align the equal sign when declaring multiple variables
- readability > functionality, don't be afraid of writing 5 lines of code more
- Use namespaces, the name should be about the functionality itself
- **DO NOT** use `using` (e.g. `using namespace std;`)
- At the end of namespace, comment it's end `} // namespace nsName`

- All parameters passed by lvalue(&) reference must be labeled const.
  
- Constants written in SNAKE_CASE
- Other use camelCase

- Public functions/objects/... -> FirstLetterUppercase
- Non-public functions/objects/... -> firstLetterLowercase

- Comment before function:
``` 
/*
nameOfTheFunction Long description of the function's function

@param nameOfTheFirstParameter Description of the first parameter
@param nameOfTheNParameter Description of the n parameter
@returns What the function returns
@note Other notes about parameter or the function itself
*/
void nameOfTheFunction(nameOfTheFirstParameter, nameOfTheNParameter){}
``` 

Order of declaration:
- libraries
- constants
- enum
- struct
- variables
- functions

Library declaration order:

1. headerfiles
2. A blank line
3. C system files.
4. C++ system files.
5. A blank line
6. Other libraries' .h files.
7. Your project's .h files.

access level order:
- public
- protected
- private


### Guideline for pull requests
* Fork the project
* Create a feature branch using the name convention *feature-dev* (e.g. *basis-dev*)
* Write your code, having patience to document it (comments in code, UML diagrams, examples of use...). This is **very important**!
* Follow the same coding convention used (style, names, ...)
* Implement significant test cases. Make sure that all tests pass.
* Create a pull request, describing what you've done.

### Guideline for maintainers
* Personally check if everything works in the code provided in PRs
* Make sure that all the tests provided pass
* If a feature is completely implemented then merge the feature branch in the *dev* branch.
* If the dev branch is relatively stable, merge it in *master* branch.
* Always look at CircleCI build results after merging / committing.

*Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live*
*- J. F. Woods*

