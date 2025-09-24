#include "AlgoGodSort.h"
#include <algorithm>
#include <random>

AlgoGodSort::AlgoGodSort() : Algo("God Sort") {}

unsigned AlgoGodSort::ListEntities(const sTeam& team, std::vector<sEntity>& entities, std::vector<sEntity*>& out)
{
    out.clear();
    
    // Random engine
    static std::mt19937 rng(0x1234); // seed fixe pour reproduire
    
    // Copie des pointeurs pour shuffle
    std::vector<sEntity*> ptrs;
    ptrs.reserve(entities.size());
    for (auto& e : entities) ptrs.push_back(&e);

    // Shuffle jusqu'à ce que tous les éléments du team soient consécutifs
    bool sorted = false;
    while (!sorted)
    {
        std::shuffle(ptrs.begin(), ptrs.end(), rng);

        sorted = true;
        bool seenTeam = false;
        bool pastTeam = false;

        for (auto* e : ptrs)
        {
            if (e->Team.Name == team.Name)
            {
                if (pastTeam) { sorted = false; break; } // les éléments de l'équipe sont après d'autres éléments
                seenTeam = true;
            }
            else
            {
                if (seenTeam) pastTeam = true;
            }
        }
    }

    // Mettre dans out uniquement ceux du team
    for (auto* e : ptrs)
    {
        if (e->Team.Name == team.Name) out.push_back(e);
    }

    return out.size();
}
