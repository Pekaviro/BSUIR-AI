#include <iostream>

#include "Person.h"
#include "Ticket.h"
#include "Audience.h"

int main() {
    int sectorCount = 3;
    Theater theater("Golden ring", sectorCount);

    Play play("Master and Margarita");

    theater.AddSector(0, "Stalls", 6, 34);
    theater.AddSector(1, "Parquet-circle", 5, 25);
    theater.AddSector(2, "Dress-circle", 3, 27);

    Person person("Ivanov", "Petr", 31, "male");

    std::vector<Audience> audienceList;
    Ticket ticket = person.BookTicket(&theater, &play, "09.11.2024", "18:30");
    ticket.ShowDetails();
    
    Audience audience1("Ivanov", "Petr", 31, "male", &ticket);

    audienceList.push_back(audience1);

    play.Perform();
    audience1.Watch(&play);

    return 0;
}