<h1 align="center">
	<a href="https://github.com/KeyC0de/ObserverPattern">Observer Pattern</a>
</h1>
<hr>


An object, called the `Subject`, maintains a list of `Observer`s and notifies them automatically of any state changes, usually by calling one of their methods.

Various nosy `Observer` (concrete) classes want to know when another object does something in which they are interested in and want to react to it in a potentially unique way.
The curious class inherits the `IObserver` interface.

The pattern promotes loose coupling since the `Subject`s don't need to know anything about the observers or listeners.

Underlying the popular, ever-present in networking, "Model View Controller" (MVC) pattern, is the observer pattern.


## Design

- All observers should have a common parent `Observer` class or interface (abstract class).
- `Observer`s subscribe to a `Subject` class upon their construction.
	* In code: They are given (dependency injection) a pointer to the `Subject`, they pass it to the base `IObserver` class's constructor, and then they call the `Subject`'s `subscribe` method with `this`/themselves as the argument.
- New subscribers are added to the observer's list.
- When the subject's state, or a subset of its state that a particular observer is interested in, is changed the Subject notifies all the interested parties on this state change, by calling one of their public methods (typically called `notify`).
- Observer objects should automatically `unsubscribe` themselves from the Subject when destroyed.


**Improvements**:</br>

An update to this system, which I don't include in this code, is "Selective notification of Observers". Meaning that an Observer usually subscribes to a particular of notification it is interested in, not to any and all actions that the Subject performs (it's typically not interested in everything). The `misc.h` header file contains various enums/flags which can be used to improve upon. I'm planning to update this repo in the future with this code, but I recommend you to do it on your own to test your understanding. It's really very simple. In reference to our example, the `LeftObserver` should only be interested when the Subject - `Car` turns left and the `RightObserver` when the `Car` turns right. So the `Car` should not notify all `m_pObservers` all the time, rather only the ones that have subscribed using a particular flag (which indicates what they're interested in).

Tip: for "multiple interests" the observers can pass along an OR of multiple flags to subscribe to multiple notifications.


Alternative terminology for this pattern includes the following:

Subscribe-Publish</br>
or Listener-Publisher</br>
or Delegate-Model</br>
or Sink-Source, where the Subject is the source of events and the Observers are sinks of events.</br>

I used Windows 8.1 x86_64, Visual Studio 2017, Modern C++17 to build the project. It should work on other platforms as well.


# Contribute

Please submit any bugs you find through GitHub repository 'Issues' page with details describing how to replicate the problem. If you liked it or you learned something new give it a star, clone it, contribute to it whatever. Enjoy.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.


# Contact

email: *nik.lazkey@gmail.com*</br>
website: *www.keyc0de.net*

