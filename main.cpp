#include "Container.h"
#include "Iterator.h"
#include "Algorithms.h"

struct Goods {
    Goods(uint32_t id = 0, const std::string& name = " ", const std::string& manufacturer = " ",
          const std::string& warehouse_address = " ", double weight = 0);
    uint32_t m_id; // Š®¤ â®¢ à 
    std::string m_name; //  §¢ ­¨¥
    std::string m_manufacturer; // à®¨§¢®¤¨â¥«ì
    std::string m_warehouse_address; // €¤à¥á áª« ¤ 
    double m_weight; // ‚¥á
};

Goods::Goods(uint32_t id, const std::string& name, const std::string& manufacturer,
             const std::string& warehouse_address, double weight) : m_id(id),
                                                                    m_name((name)),
                                                                    m_manufacturer((manufacturer)),
                                                                    m_warehouse_address((warehouse_address)),
                                                                    m_weight(weight) {

}

class func {
public:

    auto operator()(const Goods& goods) {
        return goods.m_manufacturer == "Shaurma inc.";
    }
};


int main() {
    try {
        auto Print {
                [](const Goods& value) {
                    std::cout << "Id: " << value.m_id << " Name: " << value.m_name << " Manufacturer: " << value.m_manufacturer
                              << " Address: " << value.m_warehouse_address << " Weight: " << value.m_weight << std::endl;
                }
        };

        List<Goods> cont_1{{126,"Milk","Mail ru group","October Street",1.74},
                           {5,"Snickers","MMMMM","Lenin Street",0.114},
                           {63,"Shaurma 9000","Shaurma inc.","Peace Avenue",3.33},
                           {32,"IPhone","Apple","iLoveMoneyStreet",12343.3452}};

        std::cout << "cont_1:" << std::endl;
        forEach(cont_1.begin(), cont_1.end(), Print);
        Goods first{5432,"Samsung s10","Samsung inc.","ABS street, California", 124324.124};
        Goods second{126,"Milka","Shaurma inc.","Shaurma inc.",0.1123};
        Goods third{24,"God of war","Sony","Japan, Tokio",0.001};
        List<Goods> cont_2;
        cont_2.pushBack(first);
        cont_2.pushFront(second);
        std::cout << "cont_2:" << std::endl;
        cont_2.insert(++cont_2.begin(), third);
        forEach(cont_2.begin(), cont_2.end(), Print);
        std::cout << "cont_1 after insert cont_2:" << std::endl;
        cont_1.insert(++(++cont_1.begin()), cont_2.begin(), cont_2.end());
        forEach(cont_1.begin(), cont_1.end(), Print);
        std::cout << "Sorted cont_1 by name:" << std::endl;
        
        Sort(cont_1.begin(), cont_1.end(), [](const auto& first, const auto& second) {
            return first.m_name < second.m_name;
        });
        
        forEach(cont_1.begin(), cont_1.end(), Print);
        double val;
        std::cout << "Input weight ";
        std::cin >> val;
        std::cout << "Find first object with weight more than val" << std::endl;
        auto i = findIf(cont_1.begin(), cont_2.end(), [&](const auto& s) {return s.m_weight > val;});
        Print(*i);

        i->m_warehouse_address = "Agraba";
        std::cout << "cont_1 after changes:" << std::endl;
        forEach(cont_1.begin(), cont_1.end(), Print);


        func f;
        List<Goods> cont_3(cont_1.size());
        std::cout << "Copied list with condition:" << std::endl;
        copyIf(cont_1.begin(), cont_1.end(), cont_3.begin(), f);
        forEach(cont_3.begin(), cont_3.end(), Print);
    } catch(std::exception& e) {
        std::cout << e.what();
    }
}