Release Notes
=============

## v1.0-rc2

Since the previous commit this library has been used extensively in multiple projects. This commit includes:

* A cmake script was added to the root of the project to help with testing
* Speed improvements for parsing numbers
* A std::exception derivative so that the what() member can be used in linux
* LJObject to specific type conversions no longer use asserts when an illegal type is required and instead throws an exception

There is currently only one known bug where parsing arrays does not require commas between elements. Certainly doesn't break anything but it can let poorly formatted JSON go unnoticed.

Ultimately, before 1.0 can be finalized a much more thorough testing setup needs to be implemented but as it works well enough right now we shall see when the motivation arises.

- Loren

## v1.0-rc1

This is v1.0-rc1. It has only been tested casually and not in a production
system. As it is integrated into projects and bugs/improvements arrise the
project will be updated. 

The biggest current area of concern is the generated errors for importing
JSON, they just are not very good. They will be improved as errors are encountered
"in the wild" to determine the best representation.

If you are interested in this project or have used it and have patches/suggestions
feel free to send them my way. I wrote this because I wanted something awesome
for this otherwise mundane task and it only gets there through use.

Cheers,
- Loren

LawlJSON 
========

LawlJSON is a light JSON implementation for C++ distributed under the FreeBSD license, e.g. use it to your hearts financial content. It is designed to be as simple as possible and to use pre-existing infrastructure such as the STL. For this reason it is an excellent choice for projects that need a quick file import and export. 

That said, it lacks some features found in other JSON libraries such as callback based object loading or custom data structures for everything. 

I don't care. 

I make games and all I ever wanted was a simple JSON library.

Enjoy :)

Export Example
==============

Building a structure for export is very simple. Since the two collection types
in JSON are array and object I've just mapped array to std::vector and object
to std::map. 

Literally, they are just typedefs. 

With the proper constructors and copy operators in place we can get away with
building objects and array as you can see below. Awesome!

```c++
LJObject root;
root["name"] = "Chaos";
root["function"] = "Be Awesome";
root["howHigh?"] = 9001.0;
root["tooTrue?"] = false;
root["true"] = true;
root["isNull"] = LJValue();
LJArray arr;
arr.push_back(99.234);
arr.push_back("Who");
arr.push_back(true);
arr.push_back(root);
arr.push_back(LJArray());
root["Arr!"] = arr;
```

Note that stuff like 'arr.push_back(root)' creates a copy of the object.

Now to get the exported string simply

```c++
LJString result;
Serialize(root, result);
```

Which results in (except not all pretty):

```c++
{
  "Arr!":
	  [
      99.234,
      "Who",
      true,
      {
        "function": "Be Awesome",
        "howHigh?": 9001,
        "isNull": null,
        "name": "Chaos",
        "tooTrue?": false,
        "true": true
      },
      []
    ],
  "function": "Be Awesome",
  "howHigh?": 9001,
  "isNull": null,
  "name": "Chaos",
  "tooTrue?": false,
  "true": true
}
```

Since LJString is just a std::string, you can use all your favorite stuff for
saving it out! How cool is that!?

Import Example
==============

Now importing is a little bit harder. 

Actually, I lied.

```c++
try
{
  LJValue results;
  ParseJSON(jsonText, results);
}
catch(std::exception& e)
{
  // Handle the error
}
```

Now you are free to use the data as you wish, even modify it in place and then
serialize it!