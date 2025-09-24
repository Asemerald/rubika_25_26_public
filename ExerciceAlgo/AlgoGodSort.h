#pragma once
#include "Algo.h"

class AlgoGodSort : public Algo
{
public:
    AlgoGodSort();

private:
    unsigned ListEntities(const sTeam& team, std::vector<sEntity>& entities, std::vector<sEntity*>& out) override;
};
