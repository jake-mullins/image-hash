#include <iostream>
#include <limits>
#include <string>
#include <functional>

int main(int argc, char *argv[])
{
    std::hash<std::string> strHash;

    std::string stringList[100] =   {
                                      "aware", "court", "dip", "arise", "cower", "apparatus", "fashionable", "annual", "city", "Mars", "relation", "can", "use", "farewell", "depend", "makeup", "scrape", "vegetarian", "bark", "survivor", "loan", "certain", "know", "economics", "shaft", "frame", "perceive", "suffering", "forest", "profile", "achieve", "marble", "beg", "thread", "tablet", "minority", "convention", "romantic", "estimate", "immune", "bite", "advance", "piano", "offer", "neck", "exposure", "shrink", "self", "project", "intensify", "tear", "point", "blackmail", "experience", "presence", "seasonal", "pottery", "skip", "bacon", "symbol", "land", "rocket", "attract", "volunteer", "cherry", "production", "hole", "ambiguity", "tread", "navy", "hard", "middle", "demonstrator", "contradiction", "bad", "allowance", "sow", "final", "exploit", "flock", "promotion", "claim", "concert", "fate", "post", "discount", "bitter", "cool", "we", "refer", "concentration", "creation", "radical", "blade", "design", "particle", "reproduce", "particular", "program", "radiation"
                                    };

    for(int i = 0; i < 100; ++i) {
        std::cout << strHash(stringList[i]) << std::endl;
    }

    std::cout << std::endl << strHash("generated_id_0") << std::endl << strHash("generated_id_1") << std::endl;

    std::cout << std::endl << std::numeric_limits<std::size_t>::max() << std::endl;
}