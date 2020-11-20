<h1 align="center">
	<a href="https://github.com/KeyC0de/ObserverPattern">Observer Pattern</a>
</h1>
<hr>


aka Subscribe-Publish</br>
or Listener-Publisher</br>
or Delegate-Model</br>

Underlying the MVC pattern is the observer pattern.
An object, called the subject, maintains a list of observers that and notifies them automatically of any state changes, usually by calling one of their methods.

Various nosy observer (concrete) classes wants to know when another object does something interesting that they care about and want to react to it in a potentially unique way.
The curious class defined is by the IObserver interface.

The pattern promotes loose coupling since the Subjects don't need to know anything about the observers/listeners.

**Design**

- All observers should have a common parent `Observer` class.
- Observers subscribe to a subject class upon their construction. They are given (dependency injection) a pointer to the subject, they pass it to the base `IObserver` class's constructor, and then they call the `Subject`'s `subscribe` method with `this` as argument.
- Upon an `Observer`'s their destruction they call `Subject::unsubscribe`.
- New subscribers are added to the observer's list.
- When the subject's state, or a subset of its state that the observer is interested in, is changed the Subject notifies all interested parties on this state change, by calling one of their public methods which is typically called `notify`. For this reason subjects differentiate between types of incoming events/commands.
- Observer objects should automatically unsubscribe themselves when destroyed.

I used Windows 8.1 x86_64, Visual Studio 2017, C++17 to build the project.


# Contribute

Please submit any bugs you find through GitHub repository 'Issues' page with details describing how to replicate the problem. If you liked it or you learned something new give it a star, clone it, contribute to it whatever. Enjoy.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.


# Contact

email: *nik.lazkey@gmail.com*</br>
website: *www.keyc0de.net*

