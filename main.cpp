#include <iostream>
#include "avlTree.h"
#include <iomanip>

char get_menu();

int main()
{
    
    AVL avlTree = AVL();
    
    bool done = 0;
    char selection = '0';

    int rank = 0;
    int data = 0;
    std::cout << "AVL Tree Data Structure" << std::endl << std::endl;
    while(!done)
    {
        selection = get_menu();
        
        switch(selection)
        {
            case 'a':
            case 'A':
                //insert at Rank
                std::cout << "Enter rank to insert: ";
                std::cin >> rank;
                std::cout << "Enter data (integer) to insert: ";
                std::cin >> data;
                avlTree.insertAtRank(rank, data);
                break;
            case 'd':
            case 'D':
                std::cout << "Enter rank to remove: ";
                std::cin >> rank;
                //delete node
                avlTree.removeAtRank(rank);
                break;
            case 'm':
            case 'M':
                std::cout << "Enter rank to find: ";
                std::cin >> rank;
                avlTree.elementAtRank(rank);
                break;
            case 'e':
            case 'E':
                avlTree.printAll();
                //modulo polynomials
                break;
            case 'v':
            case 'V':
                std::cout << "Enter rank to replace: ";
                std::cin >> rank;
                std::cout << "Enter data (integer) to replace: ";
                std::cin >> data;
                avlTree.replaceAtRank(rank, data);
                break;
            case 'x':
            case 'X':
                done = 1;
                break;
            default:
                std::cout << "Invalid Selection: Select an option from the menu." << std::endl;
        }
    }
    
    return 0;
}


char get_menu()
{
    char selection = '0';
    int w = 20;
    std::cout << std::left;
    std::cout << std::setw(w) << "Insert at Rank" << std::setw(5) << "(a/A)" << std::endl;
    std::cout << std::setw(w) << "Enter Rank to Find" << std::setw(5) << "(m/M)" << std::endl;
    std::cout << std::setw(w) << "Remove at Rank" << std::setw(5) << "(d/D)" << std::endl;
    std::cout << std::setw(w) << "Replace At Rank" << std::setw(5) << "(v/V)" << std::endl;
    std::cout << std::setw(w) << "Print All" << std::setw(5) << "(e/E)" << std::endl;
    std::cout << std::setw(w) << "Exit " << std::setw(5) << "(x/X)" << std::endl;
    std::cout << "Input Selection: ";
    std::cin >> selection;
    std::cout << std::endl;
    
    return selection;
    
}