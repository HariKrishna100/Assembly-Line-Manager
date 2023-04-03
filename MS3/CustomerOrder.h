// Name: Harikrishna Paresh Patel
// Seneca Student ID: 150739217
// Seneca email: hpatel296@myseneca.ca
// Date of completion: 25/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <iostream>
#include "Station.h"
namespace sdds {

	struct Item
	{
		std::string m_itemName{};
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

   class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder() = default;
		CustomerOrder(std::string& token);
		CustomerOrder(const CustomerOrder& notToCopy) {
			throw "Copying Disabled";
		};
		CustomerOrder& operator=(const CustomerOrder& notToCopy) = delete;
		CustomerOrder(CustomerOrder&& toMove) noexcept;
		CustomerOrder& operator=(CustomerOrder&& toMove) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
   };
}
#endif // !SDDS_CUSTOMERORDER_H_
