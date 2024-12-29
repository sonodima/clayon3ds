#ifndef __CLAYON3DS_DATA_H
#define __CLAYON3DS_DATA_H

#include <clay.h>

typedef struct
{
  Clay_String name;
  Clay_String introduction;
  Clay_String highlights;
} CityData;

static CityData CITIES[] = 
{
  {
    .name = CLAY_STRING("Paris"),
    .introduction = CLAY_STRING("Paris, the capital of France, is known as the 'City of Light.' Famous for landmarks like the Eiffel Tower, the Louvre, and Notre-Dame Cathedral, Paris is a center for art, fashion, and culture."),
    .highlights = CLAY_STRING("Points of Interest:\n- Eiffel Tower\n- Louvre Museum\n- Notre-Dame Cathedral\nDishes:\n- Croissant\n- Baguette\n- Escargots"),
  },
  {
    .name = CLAY_STRING("London"),
    .introduction = CLAY_STRING("London, the UK’s capital, is a vibrant city full of historic landmarks like Big Ben, Buckingham Palace, and the British Museum. It is also a cultural and financial powerhouse."),
    .highlights = CLAY_STRING("Points of Interest:\n- Big Ben\n- Buckingham Palace\n- British Museum\nDishes:\n- Fish and Chips\n- Full English Breakfast\n- Shepherd’s Pie"),
  },
  {
    .name = CLAY_STRING("Rome"),
    .introduction = CLAY_STRING("Rome, the capital of Italy, is rich in history with landmarks like the Colosseum and the Roman Forum. A must-see city blending ancient history and vibrant culture."),
    .highlights = CLAY_STRING("Points of Interest:\n- Colosseum\n- Roman Forum\n- Pantheon\nDishes:\n- Pasta Carbonara\n- Pizza Margherita\n- Gelato"),
  },
  {
    .name = CLAY_STRING("Berlin"),
    .introduction = CLAY_STRING("Berlin, Germany’s capital, is known for its modern culture and history, from the Berlin Wall to vibrant art and nightlife scenes."),
    .highlights = CLAY_STRING("Points of Interest:\n- Brandenburg Gate\n- Berlin Wall\n- Museum Island\nDishes:\n- Currywurst\n- Pretzels\n- Berliner"),
  },
  {
    .name = CLAY_STRING("Barcelona"),
    .introduction = CLAY_STRING("Barcelona, Spain’s northeastern gem, is famed for Gaudí’s architecture, including La Sagrada Família. The city blends beautiful beaches with rich culture."),
    .highlights = CLAY_STRING("Points of Interest:\n- La Sagrada Família\n- Park Güell\n- Gothic Quarter\nDishes:\n- Paella\n- Tapas\n- Churros"),
  },
  {
    .name = CLAY_STRING("Amsterdam"),
    .introduction = CLAY_STRING("Amsterdam, the Netherlands’ capital, is known for its canals and world-class museums like the Rijksmuseum and Van Gogh Museum."),
    .highlights = CLAY_STRING("Points of Interest:\n- Rijksmuseum\n- Van Gogh Museum\n- Anne Frank House\nDishes:\n- Stroopwafel\n- Haring\n- Poffertjes"),
  },
  {
    .name = CLAY_STRING("Vienna"),
    .introduction = CLAY_STRING("Vienna, Austria’s capital, is renowned for its imperial palaces, classical music, and cultural heritage from composers like Mozart and Beethoven."),
    .highlights = CLAY_STRING("Points of Interest:\n- Schönbrunn Palace\n- St. Stephen's Cathedral\n- Vienna State Opera\nDishes:\n- Wiener Schnitzel\n- Sachertorte\n- Apfelstrudel"),
  },
  {
    .name = CLAY_STRING("Prague"),
    .introduction = CLAY_STRING("Prague, the capital of the Czech Republic, is famous for its medieval architecture, with landmarks like the Charles Bridge and Prague Castle."),
    .highlights = CLAY_STRING("Points of Interest:\n- Charles Bridge\n- Prague Castle\n- Old Town Square\nDishes:\n- Svíčková\n- Goulash\n- Trdelník"),
  },
  {
    .name = CLAY_STRING("Lisbon"),
    .introduction = CLAY_STRING("Lisbon, Portugal’s capital, is a city of hills, vibrant neighborhoods, and iconic landmarks like the Belém Tower and MAAT museum."),
    .highlights = CLAY_STRING("Points of Interest:\n- Belém Tower\n- MAAT Museum\n- Alfama District\nDishes:\n- Bacalhau\n- Pastéis de Nata\n- Caldo Verde"),
  },
  {
    .name = CLAY_STRING("Budapest"),
    .introduction = CLAY_STRING("Budapest, Hungary's capital, is known for its grand architecture, historic thermal baths, and landmarks like Buda Castle and the Parliament."),
    .highlights = CLAY_STRING("Points of Interest:\n- Buda Castle\n- Hungarian Parliament\n- Fisherman’s Bastion\nDishes:\n- Goulash\n- Langos\n- Chimney Cake"),
  },
  {
    .name = CLAY_STRING("Athens"),
    .introduction = CLAY_STRING("Athens, the cradle of Western civilization, is home to the ancient Parthenon and other historic ruins. It’s a mix of ancient history and modern life."),
    .highlights = CLAY_STRING("Points of Interest:\n- Parthenon\n- Acropolis Museum\n- Temple of Olympian Zeus\nDishes:\n- Souvlaki\n- Moussaka\n- Tzatziki"),
  },
  {
    .name = CLAY_STRING("Stockholm"),
    .introduction = CLAY_STRING("Stockholm, Sweden’s capital, is known for its stunning archipelago and landmarks like the Royal Palace and Gamla Stan."),
    .highlights = CLAY_STRING("Points of Interest:\n- Royal Palace\n- Gamla Stan\n- ABBA Museum\nDishes:\n- Swedish Meatballs\n- Gravlax\n- Räkor"),
  },
  {
    .name = CLAY_STRING("Copenhagen"),
    .introduction = CLAY_STRING("Copenhagen, Denmark’s capital, is famous for its cozy atmosphere and landmarks like Nyhavn and Tivoli Gardens. The city promotes sustainable living."),
    .highlights = CLAY_STRING("Points of Interest:\n- Nyhavn\n- Tivoli Gardens\n- Little Mermaid Statue\nDishes:\n- Smørrebrød\n- Danish Pastry\n- Frikadeller"),
  },
  {
    .name = CLAY_STRING("Madrid"),
    .introduction = CLAY_STRING("Madrid, Spain’s capital, is a lively city known for its historic landmarks, including the Royal Palace and Prado Museum. It’s a vibrant cultural hub."),
    .highlights = CLAY_STRING("Points of Interest:\n- Royal Palace\n- Prado Museum\n- Retiro Park\nDishes:\n- Paella\n- Churros\n- Tapas"),
  },
  {
    .name = CLAY_STRING("Helsinki"),
    .introduction = CLAY_STRING("Helsinki, Finland’s capital, offers a blend of design-forward architecture and natural beauty, with landmarks like Helsinki Cathedral and Suomenlinna."),
    .highlights = CLAY_STRING("Points of Interest:\n- Helsinki Cathedral\n- Suomenlinna\n- Design District\nDishes:\n- Karjalanpiirakka\n- Kalakukko\n- Lohikeitto"),
  },
  {
    .name = CLAY_STRING("Edinburgh"),
    .introduction = CLAY_STRING("Edinburgh, Scotland’s capital, is rich in history with landmarks like Edinburgh Castle and the Royal Mile. The city is also famous for its festivals."),
    .highlights = CLAY_STRING("Points of Interest:\n- Edinburgh Castle\n- Royal Mile\n- Arthur’s Seat\nDishes:\n- Haggis\n- Shortbread\n- Scotch Whisky"),
  },
  {
    .name = CLAY_STRING("Oslo"),
    .introduction = CLAY_STRING("Oslo, Norway’s capital, is known for its modern architecture and cultural attractions, including the Viking Ship Museum and Opera House."),
    .highlights = CLAY_STRING("Points of Interest:\n- Viking Ship Museum\n- Oslo Opera House\n- Akershus Fortress\nDishes:\n- Raspeballer\n- Lutefisk\n- Kjøttkaker"),
  },
  {
    .name = CLAY_STRING("Zurich"),
    .introduction = CLAY_STRING("Zurich, Switzerland’s largest city, is known for its high quality of life, medieval Old Town, and as a financial hub."),
    .highlights = CLAY_STRING("Points of Interest:\n- Lake Zurich\n- Old Town\n- Swiss National Museum\nDishes:\n- Fondue\n- Rösti\n- Zürcher Geschnetzeltes"),
  },
  {
    .name = CLAY_STRING("Dubrovnik"),
    .introduction = CLAY_STRING("Dubrovnik, Croatia’s Adriatic gem, is a medieval city with stunning city walls and historic buildings, earning it the nickname 'Pearl of the Adriatic.'"),
    .highlights = CLAY_STRING("Points of Interest:\n- City Walls\n- Old Town\n- Fort Lovrijenac\nDishes:\n- Pasticada\n- Grilled Fish\n- Black Risotto"),
  },
  {
    .name = CLAY_STRING("Brussels"),
    .introduction = CLAY_STRING("Brussels, Belgium’s capital, is famous for its mix of French and Flemish culture, and for landmarks like the Grand Place and Atomium."),
    .highlights = CLAY_STRING("Points of Interest:\n- Grand Place\n- Atomium\n- Manneken Pis\nDishes:\n- Belgian Waffles\n- Frites\n- Moules-Frites"),
  },
};

#define NUM_CITIES (sizeof(CITIES) / sizeof(CityData))

#endif // __CLAYON3DS_DATA_H
