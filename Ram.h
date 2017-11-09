//
// Created by conrad on 11/7/17.
//

/* This is the RAM class which is controlled by an MMU object. No one but the MMU can manage this.
 * read: returns a string at a specific address.
 * write: writes a data to a specific address.
 * write: writes a vector of strings to a specific address
 * SIZE: The total number of RAM locations
 * Ram(): The basic constructor for RAM
 * ~RAM(): Deletes the RAM object; no other cleanup required
 */

#ifndef PHASE_2_RAM_H
#define PHASE_2_RAM_H
#include <mutex>
#include <vector>
#include <string>

class Ram
{
    public:
        std::string read(int address);
        void write(int address, std::string data);
        void write(int address, std::vector<std::string> s);
        const static int SIZE = 1024;
        Ram();
        ~Ram();
        static void testRam();

    private:
        std::string ram_data[SIZE];
        int ram_used;
};



#endif //PHASE_2_RAM_H

