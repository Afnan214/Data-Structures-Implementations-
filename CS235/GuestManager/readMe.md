In this assignment, lets create some kind of hotel management component.

=========================================================

 

Create modern C++ enumeration (enum class) called RoomType with two items in it, Standard and Comfort. You can find a description of such modern C++ enumerations using the following link (and in million other places too):

https://www.codesdope.com/cpp-enum-class/

Keep in mind, enum instances are small. It is ok to pass enum instance by copy.

=========================================================

 

Create modern C++ enumeration (enum class) called GuestType with three items in it, Family, Businessman, and Rockstar. Behavior of each guest type is the following:

Family. Nothing special.
Businessman. Businessman generates additional income each day (by actively using the items from the room refrigerator).
Rockstar. Rockstar keeps room occupied for additional 10 days (because rockstar is a fool and completely thrashes the room so it requires a full 10-day renovation after the rockstar checks out). Pay attention, rockstar pays only for the days that were booked, but the room is occupied longer than booked.
Both RoomType and GuestType enumerations are meant to be visible to users of your library.

=========================================================

 

Create an abstract Guest class. It has the following mandatory parts in it

Protected fields for
Type of the occupied room
Type of the guest
booked number of days
there should be no additional income field
GetGuestType – a getter (a.k.a accessor) for a type of the guest
GetRoomType – a getter for a type of the room.
GetBookedDays – a getter for a number of the booked days
GetRoomBusyDays – purely virtual function that returns number of days that the room will be in use. This method will behave differently for different types of guests. Remember, that rockstar books and pays for a certain number of days, but the room stays busy for 10 days longer.
int GetAdditionalIncome – purely virtual function that returns an amount of money generated each day in addition to the room cost. Remember, that businessmen generate additional income. Everybody else will return a default 0.
Guest( GuestType, RoomType, StayDuration ) – parametrized constructor that creates a new guest of specified type that occupies a room of a specified type for a specified number of days.
~Guest – virtual destructor. It does nothing in this class, but since we plan to inherit from this class, it is necessary.
There should be no setter (a.k.a mutator) methods for Guest fields.
From the Guest class inherit three classes

class Family. The most regular Guess sub-class with nothing special in it. For a family, days booked equal to room busy day, and there is no additional income.
class Rockstar. As discussed before, the number of days the room is busy is 10 days longer than the days booked for a rockstar. There is no additional income.
class Businessman. Objects of Businessman class has an additional income int field and the following parametrized constructor
Businessman( GuestType, RoomType, stayDuration, additionalIncome )
Pay attention, there are no setters (a.k.a mutators) for fields of the base class Guest. You’ll have to activate the parametrized constructor of Guest from the constructor of Businessman. The modern C++ constructor syntax allows you to do it.
=========================================================

 

Create GuestManager class. This class stores inside information about current hotel guests. Guests will be represented as objects of Guest subclasses. Most likely you’ll have a vector of pointers to Guest class. Here is a bunch of things that MUST be in your class.

GuestManager (int #OfStandardRooms, int dayPriceStandard, int #OfComfortRooms, int dayPriceComfort)
This is a parametrized constructor for GuestManager class. It accepts the number of rooms of each type and “per day” room prices for each room type.

 

bool AddGuest(GuestType, RoomType, int stayDays, int additionalIncome)
Adds a guest of specified type into a room of specified type for a specified number of days. AddGuest returns true if the guest was successfully placed in the hotel and false if otherwise. Failure to place a guest can be caused by all rooms of specified type already occupied.
additionalIncome variable has a default value of 0. It is used for Businessman object creation only. In case you need a reminder of default function parameters in C++, you can find it for example here:
https://www.geeksforgeeks.org/default-arguments-c/

 

bool IsAvailable(RoomType, int inDays)
IsAvalable returns true if a room of a specified type will be available in a specified number of days. Otherwise, IsAvalable returns false.

Make a default value of inDays equal to 0. In case you need a reminder of default function parameters in C++, you can find it for example here:
https://www.geeksforgeeks.org/default-arguments-c/

For example, if the room is occupied for 3 days, then in 3 days (inDays==3) it will be available again.

 

int IncomingProfit()
IncommingProfit returns the sum of money that all current guests will pay (including all predicted additional income from the current businessmen guests).

float EarningEfficiency()
EarningEfficiency returns current earning efficiency
earning_efficiency = current_per_day_income/max_per_day_income
max_per_day_income is the sum of base day prices of all existing rooms.
current_per_day_income is the sum of base day prices of all currently occupied rooms plus all additional income generated per day the by current businessmen guests.
Since businessman can generate additional income, it is theoretically possible to have earning efficiency above 1.0


bool operator<(another object of GuestManager class) – comparison  operator. GuestManager A is less than GuestManager B if A.IncomingProfit() is less than B.IncomingProfit(). Use our textbook as a reference of how to override operators.
You are responsible for preventing memory leaks! It means that you are responsible for releasing all dynamically allocated memory once the object of GuestManager goes out of scope. It means that you need a destructor. I don’t put destructor as a mandatory item in case someone will go for advanced smartpointers (in this case, you can just leave the class with default destructor). Using smartpointers is not mandatory, but acceptable. In case you do use them, prefer unique_ptr over shared_ptr whenever possible.