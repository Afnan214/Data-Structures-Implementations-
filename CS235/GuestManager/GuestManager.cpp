#include "GuestManager.h"

Guest::Guest(const GuestType& person, const RoomType& room, const int& StayDuration) :
	GT(person), RT(room), BookedDays(StayDuration) {}
GuestType Guest::GetGuestType()
{
	return GT;
}
RoomType Guest::GetRoomType()
{
	return RT;
}
int Guest::GetBookedDays()
{
	return BookedDays;
}
Guest:: ~Guest() {}
Family::Family(const GuestType& person, const RoomType& room, const int& StayDuration) :
	Guest(person, room, StayDuration) {}
int Family::GetRoomBusyDays()
{
	return GetBookedDays();
}
int Family::GetAdditionalIncome()
{
	return 0;
}
Family::~Family() {}
Rockstar::Rockstar(const GuestType& person, const RoomType& room, const int& StayDuration) :
	Guest(person, room, StayDuration) {}
int Rockstar::GetRoomBusyDays()
{
	int num_of_days = GetBookedDays() + 10;
	return num_of_days;
}
int Rockstar::GetAdditionalIncome()
{
	return 0;
}
Rockstar:: ~Rockstar() {}
Businessman::Businessman(const GuestType& person, const RoomType& room, const int& StayDuration, const int& additionalIncome) :
	Guest(person, room, StayDuration)
{
	extra_income = additionalIncome;
}

int Businessman::GetRoomBusyDays()
{
	return GetBookedDays();
}
int Businessman::GetAdditionalIncome()
{
	return (extra_income * GetBookedDays());
}
Businessman:: ~Businessman() {}
GuestManager::GuestManager(const int& numOfStandardRooms, const int& dayPriceStandard, const int& numOfComfortRooms, const int& dayPriceComfort) :
	standard_rooms(numOfStandardRooms), standard_price(dayPriceStandard), comfort_rooms(numOfComfortRooms), comfort_price(dayPriceComfort) {}

bool GuestManager::AddGuest(const GuestType& type_of_guest, const RoomType& type_of_room, const int& stayDays, const int& additionalIncome)
{
	if (stayDays == 0)
	{
		return false;
	}
	else
	{
		if (type_of_room == RoomType::Standard)
		{
			if (stand_count < standard_rooms)
			{
				if (type_of_guest == GuestType::Family)
				{
					Family* ptr = new Family(type_of_guest, type_of_room, stayDays);
					hotel_bookings.push_back(ptr);
				}
				else if (type_of_guest == GuestType::Rockstar)
				{
					Rockstar* ptr = new Rockstar(type_of_guest, type_of_room, stayDays);
					hotel_bookings.push_back(ptr);
				}
				else
				{
					Businessman* ptr = new Businessman(type_of_guest, type_of_room, stayDays, additionalIncome);
					hotel_bookings.push_back(ptr);
				}
				stand_count++;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (comf_count < comfort_rooms)
			{
				if (type_of_guest == GuestType::Family)
				{
					Family* ptr = new Family(type_of_guest, type_of_room, stayDays);
					hotel_bookings.push_back(ptr);
				}
				else if (type_of_guest == GuestType::Rockstar)
				{
					Rockstar* ptr = new Rockstar(type_of_guest, type_of_room, stayDays);
					hotel_bookings.push_back(ptr);
				}
				else
				{
					Businessman* ptr = new Businessman(type_of_guest, type_of_room, stayDays, additionalIncome);
					hotel_bookings.push_back(ptr);

				}
				comf_count++;
				return true;

			}
			else
			{
				return false;
			}
		}
	}

}

bool GuestManager::IsAvailable(const RoomType& type_of_room, const int& inDays)
{
	for (auto hotel_guest : hotel_bookings)
	{
		if (type_of_room == RoomType::Standard)
		{
			if (standard_rooms > stand_count)
			{
				return true;
			}
			else if (hotel_guest->GetRoomType() == type_of_room)
			{
				if (hotel_guest->GetRoomBusyDays() <= inDays)
				{
					return true;
				}
			}

		}
		else if (type_of_room == RoomType::Comfort)
		{
			if (comfort_rooms > comf_count)
			{
				return true;
			}
			else if (hotel_guest->GetRoomType() == type_of_room)
			{
				if (hotel_guest->GetRoomBusyDays() <= inDays)
				{
					return true;
				}
			}
		}
	}
	return false;

}

int GuestManager::IncomingProfit()
{

	for (auto hotel_guest : hotel_bookings)
	{
		if (hotel_guest->GetRoomType() == RoomType::Standard)
		{
			profit += hotel_guest->GetBookedDays() * standard_price;
			profit += hotel_guest->GetAdditionalIncome();
		}
		else
		{
			profit += hotel_guest->GetBookedDays() * comfort_price;
			profit += hotel_guest->GetAdditionalIncome();
		}
	}
	return profit;
}

float GuestManager::EarningEfficiency()
{
	if (profit != 0)
	{
		float curr_per_day_income = float((stand_count * standard_price) + (comf_count * comfort_price));
		for (auto hotel_guest : hotel_bookings)
		{
			curr_per_day_income += float((hotel_guest->GetAdditionalIncome()) / (hotel_guest->GetBookedDays()));
		}

		float max_per_day_income = (float(standard_rooms) * float(standard_price)) + (float(comfort_rooms) * float(comfort_price));


		return curr_per_day_income / max_per_day_income;
	}
	else { return 0.0f; }
}

bool GuestManager:: operator<(const GuestManager& hotel)
{
	if (profit < hotel.profit)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;


}

GuestManager:: ~GuestManager()
{
	for (auto hotel_guest : hotel_bookings)
	{
		delete hotel_guest;
	}

}