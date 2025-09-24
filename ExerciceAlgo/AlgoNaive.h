#pragma once
#include "Algo.h"

class AlgoNaive : public Algo
{
public:
    AlgoNaive();

private:
    unsigned ListEntities(const sTeam& team, std::vector<sEntity>& entities, std::vector<sEntity*>& out) override;
};