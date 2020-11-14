# Readme

A tutorial on the popular Observer design pattern.
With nice cozy file class separation.

aka Subscribe-Publish
or Listener-Publisher
or Delegate-Model

Underlying the MVC (Model View Controller) pattern is the observer pattern.
An object, called the subject, maintains a list of observers that and notifies them automatically of any state changes, usually by calling one of their methods.

Various nosy observer (concrete) classes wants to know when another object does something interesting that they care about and want to react to it in a potentially unique way.
The curious class defined is by the IObserver interface.

The pattern promotes loose coupling since the Subjects don't need to know anything about the observers/listeners.

Design
- All observers should have a common parent `Observer` class.
- Observers subscribe to a subject class upon their construction. They are given (dependency injection) a pointer to the subject, they pass it to the base `IObserver` class's constructor, and then they call the `Subject`'s `subscribe` method with `this` as argument.
- Upon an `Observer`'s their destruction they call `Subject::unsubscribe`.
- New subscribers are added to the observer's list.
- When the subject's state, or a subset of its state that the observer is interested in, is changed the Subject notifies all interested parties on this state change, by calling one of their public methods which is typically called `notify`. For this reason subjects differentiate between types of incoming events/commands.
- Observer objects should automatically unsubscribe themselves when destroyed.


Enjoy.
