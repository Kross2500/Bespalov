#include <iostream>
#include <fstream>
#include <string>
#include <clocale> 


struct prod
{
    std::string nazv;
    double zena;
    double kolvo;
};

void addProductToFile(const prod& prd)
{
    std::ofstream outFile("products.txt", std::ios::app);
    if (outFile.is_open())
    {
        outFile << prd.nazv << "," << prd.zena << "," << prd.kolvo << std::endl;
        outFile.close();
        std::cout << "Вы добавили продукт." << std::endl;
    }
    else 
    {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

void searchProductByTitle(const std::string& title) 
{
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) 
    {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) 
        {
            size_t pos = line.find(',');
            std::string nazv = line.substr(0, pos);
            if (nazv == title) 
            {
                std::cout << "Найден продукт: " << line << std::endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) 
        {
            std::cout << "Продукт с таким наименованием не найден." << std::endl;
        }
    }
    else 
    {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void searchProductByZena(const double& zenna) 
{
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) 
    {
        std::string line;
        bool found = false;
        int cnt = 0;
        while (std::getline(inFile, line)) 
        {
            int pos1 = line.find(',');
            int pos2 = line.find_last_of(',');
            double zenah = std::stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            //std::cout << zenah << std::endl;
            if (zenah < zenna || zenah == zenna) 
            {

                if (cnt == 0)
                {
                    std::cout << "Найденные продукты: " << std::endl << line << std::endl;
                    cnt++;
                }
                else std::cout << line << std::endl;
                found = true;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "Продукты ниже этой цены не найдены." << std::endl;
        }
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}


void sortsProductsByZena() 
{
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) 
    {
        std::string lines[100]; 
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) 
        {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) 
        {
            for (int j = 0; j < count - i - 1; j++) 
            {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double zena1 = std::stod(lines[j].substr(pos1 + 1));
                double zena2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (zena1 < zena2) 
                {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // Запись отсортированных данных обратно в файл
        std::ofstream outFile("products.txt");
        if (outFile.is_open()) 
        {
            for (int i = 0; i < count; i++) 
            {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Продукты отсортированы по цене." << std::endl;
        }
        else 
        {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    }
    else 
    {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "russian");
    int choice;
    std::string title;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Поиск продукта по названию" << std::endl;
        std::cout << "3. Сортировать продуктов по цене" << std::endl;
        std::cout << "4. Поиск продуктов по верхней цене" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите команду: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            std::cin.ignore();
            std::string nazv;
            double zena, kolvo;
            std::cout << "Введите название продукта: ";
            std::getline(std::cin, nazv);
            if (nazv.empty()) 
            {
                std::cout << "Ввод прерван." << std::endl;
                break;
            }
            std::cout << "Введите цену товара: ";
            std::cin>> zena;
            std::cout << "Введите кол-во продукта: ";
            std::cin >> kolvo;
            prod newprod { nazv, zena, kolvo };
            addProductToFile(newprod);
            break;
        }
        case 2: 
        {
            std::cin.ignore();
            std::cout << "Введите наименование товара для поиска: ";
            std::getline(std::cin, title);
            searchProductByTitle(title);
            break;
        }
        case 3: 
        {
            sortsProductsByZena();
            break;
        }
        case 4: 
        {
            std::cin.ignore();
            std::cout << "Введите ценовое ограничение для поиска: ";
            double zenna;
            std::cin >> zenna;
            searchProductByZena(zenna);
            break;
        }
        case 0: {
            std::cout << "Вы вышли." << std::endl;
            break;
        }
        default: 
        {
            std::cout << "Нет такой команды" << std::endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
