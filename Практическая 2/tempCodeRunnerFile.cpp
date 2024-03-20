case 2:
        if (!isDecreasing(arr)) {
            std::cout << "Массив упорядочен не в порядке убывания, удаляем значения, содержащие цифру 5" << "\n";
            removeValueWithFive(arr);
        } else {
            std::cout << "Массив упорядрчен в порядке убывания.";
        }
        std::cout << "Результирующий массив: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        break;