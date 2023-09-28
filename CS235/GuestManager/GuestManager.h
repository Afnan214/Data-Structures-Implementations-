#ifndef GuestManagers
#define GuestManagers
#include <iostream>
#include <vector>
//abstract base class

enum class RoomType
{
	Standard,
	Comfort
};
enum class GuestType
{
	Family,
	Businessman,
	Rockstar
};

class Guest
{
public:
	Guest(const GuestType& person, const RoomType& room, const int& StayDuration);
	GuestType GetGuestType();			//will return Guest Type


	RoomType GetRoomType();			//will return Room Type

	int GetBookedDays();			//Will return number of
	virtual int GetRoomBusyDays() = 0;
	virtual int  GetAdditionalIncome() = 0;
	virtual ~Guest();
protected:
	GuestType GT;						//GuestType
	RoomType RT;						//RoomType 
	const unsigned int BookedDays;		//booked number of days
};
class Family : public Guest
{
public:
	Family(const GuestType& person, const RoomType& room, const int& StayDuration);
	virtual int GetRoomBusyDays() override;
	virtual int GetAdditionalIncome() override;
	virtual ~Family();

};
class Rockstar : public Guest
{
public:
	Rockstar(const GuestType& person, const RoomType& room, const int& StayDuration);
	virtual int GetRoomBusyDays() override;
	virtual int GetAdditionalIncome() override;
	virtual ~Rockstar();

};
class Businessman : public Guest
{
public:
	Businessman(const GuestType& person, const RoomType& room, const int& StayDuration, const int& additionalIncome);
	virtual int GetRoomBusyDays() override;
	virtual int GetAdditionalIncome() override;
	virtual ~Businessman();
protected:
	unsigned int extra_income;
};






class GuestManager
{
private:
	int profit = 0;
public:
	GuestManager(const int& numOfStandardRooms, const int& dayPriceStandard, const int& numOfComfortRooms, const int& dayPriceComfort);
	bool AddGuest(const GuestType& type_of_guest, const RoomType& type_of_room, const int& stayDays, const int& additionalIncome = 0);
	bool IsAvailable(const RoomType& type_of_room, const int& inDays = 0);
	int IncomingProfit();
	float EarningEfficiency();
	bool operator<(const GuestManager& hotel_uno);
	~GuestManager();

protected:
	const unsigned int standard_rooms;
	const unsigned int standard_price;
	const unsigned int comfort_rooms;
	const unsigned int comfort_price;
	unsigned int stand_count = 0;
	unsigned int comf_count = 0;


	std::vector<Guest*> hotel_bookings = {};



};

#endif