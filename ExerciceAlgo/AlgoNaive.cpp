#include "AlgoNaive.h"

AlgoNaive::AlgoNaive() : Algo("Naive") {}

/**
 * A naive algorithm would just iterate through the list and pick the entities that match the team.
 * @param team 
 * @param entities 
 * @param out 
 * @return 
 */
unsigned AlgoNaive::ListEntities(const sTeam& team, std::vector<sEntity>& entities, std::vector<sEntity*>& out)
{
    out.clear();
    for (auto& e : entities)
    {
        if (e.Team.Name == team.Name)
        {
            out.push_back(&e);
        }
    }
    return out.size();
}
