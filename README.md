# Game-Engine
Game Engine For Making Games Quick

# Needed
- SFML
- Code::Blocks
- C++ 14
# Documentation
___

Objects
- x
- y
- width (resx)
- height (resy)
- move Function (move)
- draw (needs sf::RenderWindow)

Text
- same as object, but as a SFML text object

Button
- same as object, but has a callback to a void function without parameters
- callback triggers when clicked

ObjectManager
- Objects (a C++ Vector)
- Texts (holds all text objects)
- Buttons (holds all button objects)
- Check For Touch Function (isTouch) (needs the indices)
- Add Object Function (push_back) (can use to add any object(Objects, Texts, or Buttons))
- A draw function that draws all objects (needs sf::RenderWindow)
