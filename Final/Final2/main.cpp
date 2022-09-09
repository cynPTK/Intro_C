#include <iostream>
#include <cassert>
using namespace std;

class Dispenser
{
public:
    Dispenser();
    // A Dispenser has a capacity of 150 cans and has no cans
    // in it when created.
    int addCans(int num);
    // Attempt to add num cans to the dispenser, but
    // don't fill the dispenser beyond its capacity.  The function
    // returns the number of cans actually added, which will be
    // less than the requested number if adding the requested number
    // of cans would overfill the dispenser.
    bool dispenseCan();
    // Attempt to dispense one can from the dispenser
    // (e.g., to dispense to a customer).  If the dispenser is
    // empty, simply return false; otherwise, remove one can
    // from the dispenser and return true.
    int numCans() const;
private:
    int m_numCans;
    int m_capacity;
};

Dispenser::Dispenser()
{
    m_numCans = 0;
    m_capacity = 150;
}

int Dispenser::numCans() const
{
    return m_numCans;
}
int Dispenser::addCans(int num)
{
    if (num <= 0)
        return 0;
    if (m_numCans + num > m_capacity)
        num = m_capacity - m_numCans;
    m_numCans += num;
    return num;
}

bool Dispenser::dispenseCan()
{
    if (m_numCans == 0)
        return false;
    m_numCans--;
    return true;
}

class VendingMachine
{
public:
    VendingMachine(int price, int startAmount);
    int addCans(int num);
    int purchase(int amt);
    int moneyRetained() const;
    int numCans();
    int price() const;
private:
    Dispenser m_dispenser;
    int       m_price;
    int       m_totalMoneyKept;
};

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE VendingMachine MEMBER FUNCTIONS

VendingMachine::VendingMachine(int price, int startAmount)
{
    m_price = price;
    m_dispenser.addCans(startAmount);
    m_totalMoneyKept = 0;
}

int VendingMachine::numCans()
{
    return m_dispenser.numCans();
}

int VendingMachine::addCans(int num)
{
    return m_dispenser.addCans(num);
}

int VendingMachine::purchase(int amt)
{
    int numcans = amt / m_price;
    int cansSold = 0;
    for (int i = 0; i<numcans; i++)
    {
        if (m_dispenser.dispenseCan())
        {
            cansSold++;
        }
        else
            break;
    }
    int cost = cansSold * m_price;
    m_totalMoneyKept += cost;
    int change = amt - cost;

    return change;
}

int VendingMachine::moneyRetained() const
{
    return m_totalMoneyKept;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE VendingMachine MEMBER FUNCTIONS

VendingMachine* createVM()
{
    VendingMachine* newVM = new VendingMachine(6, 150);
    newVM->purchase(90);
    return newVM;
}
int main()
{
    VendingMachine vm(5, 25);      // 25 cans to start, each will cost 5 blorks
    assert(vm.addCans(35) == 35);  // So now vm holds 60 cans
    cout << vm.numCans();
    assert(vm.purchase(47) == 2);  // 9 cans dispensed, 2 blorks change
    cout << vm.numCans();
    assert(vm.moneyRetained() == 45);  // vm retains 45 blorks so far
    VendingMachine* ptr = createVM();
    cout <<ptr->numCans();
    delete ptr;

    cout << "All tests succeeded" << endl;
}

