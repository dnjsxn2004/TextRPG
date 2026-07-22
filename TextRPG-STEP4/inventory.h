#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <iostream>
#include <algorithm>

template<typename T>
class InventoryArry_T
{
private:
	T* pItem_;
	int capacity_;
	int size_;

public:

	InventoryArry_T(int capacity_)
		: capacity_(capacity_), size_(0)
	{
		pItem_ = new T[capacity_];

	};

	// pItem 소멸자
	~InventoryArry_T()
	{
		delete[] pItem_;
	}

	T& operator[](int index) // inventory[i]
	{
		return pItem_[index];
	}
	
	// 아이템 넣기 push_back 대체
	void AddItem(const T& item) 
	{
		if (size_ >= capacity_)
		{
			std::cout << "inventory is full" << std::endl;
			std::cout << "Adding Item..." << "(" << size_ << "/" << capacity_ << "full )" << std::endl;
			std::cout << "-> Inventory auto-expanded! " << "(" << capacity_ << "->" << capacity_ + 10 << ")" << std::endl;

			Resize(capacity_ + 10);

		}

		pItem_[size_] = item;
		size_++;
	}
	
	// 아이템 제거
	void RemoveLastItem(int index)
	{
		if (index < 0 || index >= size_)
		{
			std::cout << "Invalid item index." << std::endl;
			return;
		}

		for (int i = index; i < size_ - 1; i++)
		{
			pItem_[i] = pItem_[i + 1];
		}

		size_--;
	}
	
	// 모든 아이템 출력 item 구조체의 printinfo 쓰기?
	void PrintAllItem()
	{

		if (size_ == 0)
		{
			std::cout << "inventory is empty" << std::endl;

			return;
		}

		SortItems();

		for (int i = 0; i < size_; i++)
		{
			pItem_[i].printInfo();
		}


	}
	
	// 인벤토리 내부 아이템 갯수 가져오기 size 대체
	int GetSize()
	{
		return size_;
	}
	
	// 인벤토리 크기 구하기 capacity 대체
	int GetCapacity()
	{
		return capacity_;
	}
	
	// empty 대체
	bool IsEmpty()
	{
		return size_ == 0;
	}
	
	// back 대체 전투중 아이템 선택에 필요
	T& Back()
	{
		return pItem_[size_ - 1];
	}

	// 인벤토리 리사이즈
	void Resize(int newCapacity)
	{
		if (newCapacity >= size_)
		{
			T* newpItem_ = new T[newCapacity];

			for (int i = 0; i < size_; i++)
			{
				newpItem_[i] = pItem_[i];
			}

			delete[] pItem_;

			pItem_ = newpItem_;

			capacity_ = newCapacity;

		}
		else
		{
			std::cout << "Select a valid number" << std::endl;
		}

	}

	// 아이템 가격 비교 함수
	static bool compareByPrice(const T& a, const T& b)
	{
		if (a.price > b.price)
		{
			return true;
		}
		
		return false;
	}

	// 인벤토리 정렬(가격 기준)
	void SortItems()
	{
		std::sort(pItem_, pItem_ + size_, compareByPrice);
	}
};

#endif // INVENTORY_H_


/*
 
 인벤토리 교체 목록


 인벤토리 선언
vector<Item> inventory;
inventory.reserve(10);

inventory.size()  인벤토리 내부 아이템 갯수
inventory.capacity() 인벤토리 크기
inventory.empty() 인벤토리 비었는지
inventory.push_back(item) 인벤토리에 넣기
inventory.erase(inventory.begin() + Itemindex) 사용후 제거
inventory.back() 마지막 아이템
inventory.begin() 인벤토리 첫번째 원소

매개변수도 교체
*/