//
// Created by Danial Dervovic on 05/04/2017.
//

#include "gtest/gtest.h"
#include "BipartiteGraph.h"
#include "BicliqueFinder.h"
#include <math.h>

TEST(biclique_finder_test, constructor) {

    const std::vector<std::vector<int>> & mat = {{0,1,1}, {1,0,0}, {0,1,0}, {1,1,1}};
    BipartiteGraph graph = BipartiteGraph(mat);
    BicliqueFinder finder = BicliqueFinder(graph);
    ASSERT_EQ(finder.get_LRPQ_initial(), "1 2 3 4 \n\n5 6 7 \n\n");

}

TEST(biclique_finder_test, get_maximal_throws) {
    const std::vector<std::vector<int>> & mat = {{0,1,1}, {1,0,0}, {0,1,0}, {1,1,1}};
    BipartiteGraph graph = BipartiteGraph(mat);
    BicliqueFinder finder = BicliqueFinder(graph);
    ASSERT_ANY_THROW(finder.get_maximal_bicliques());
    ASSERT_ANY_THROW(finder.get_num_bicliques());
}

std::vector<std::vector<int>> J_minus_I(unsigned long n) {
    // makes n x n matrix of ones apart from the main diagonal, which is all zeros

    std::vector<std::vector<int>> mat(n, std::vector<int>(n,1));
    for (int i = 0; i < mat.size(); i++) {
        mat[i][i] = 0;
    }

    return mat;

}

TEST(biclique_finder_test, biclique_find_max_num) {

    std::vector<std::string> algos = {"improved", "standard"};

    for (int idx = 0; idx < algos.size(); idx++) {

        std::string algorithm = algos[idx];

        // Case with maximum possible maximal bicliques
        for (unsigned long n = 3; n < 9; n++) {

            /* Case with most maximal bicliques */
            std::vector<std::vector<int>> mat = J_minus_I(n);

            BipartiteGraph graph = BipartiteGraph(mat);
            BicliqueFinder finder = BicliqueFinder(graph);

            finder.find_maximal_bicliques(algorithm);

            auto bicliques = finder.get_maximal_bicliques();
            int num_bicliques = finder.get_num_bicliques();

            ASSERT_EQ(num_bicliques, finder.max_number_possible);

        }
    }
}

TEST(biclique_finder_test, biclique_find_min_num) {

    std::vector<std::string> algos = {"improved", "standard"};

    for (int idx = 0; idx < algos.size(); idx++) {

        std::string algorithm = algos[idx];

        /* Cases with fewest maximal bicliques */

        for (unsigned long n = 3; n < 9; n++) {
            // complete bipartite graph (left set bigger)
            std::vector<std::vector<int>> J1(n + 3, std::vector<int>(n, 1));
            BicliqueFinder finder_J1 = BicliqueFinder(BipartiteGraph(J1));
            finder_J1.find_maximal_bicliques(algorithm);
            ASSERT_EQ(finder_J1.get_num_bicliques(), 1);
        }

        for (unsigned long n = 3; n < 9; n++) {

            // complete bipartite graph (right set bigger)
            std::vector<std::vector<int>> J2(n, std::vector<int>(n + 2, 1));
            BicliqueFinder finder_J2 = BicliqueFinder(BipartiteGraph(J2));
            finder_J2.find_maximal_bicliques(algorithm);
            ASSERT_EQ(finder_J2.get_num_bicliques(), 1);

        }

        for (unsigned long n = 3; n < 9; n++) {
            // complete bipartite graph (left, right equal)
            std::vector<std::vector<int>> J3(n, std::vector<int>(n, 1));
            BicliqueFinder finder_J3 = BicliqueFinder(BipartiteGraph(J3));
            finder_J3.find_maximal_bicliques(algorithm);
            ASSERT_EQ(finder_J3.get_num_bicliques(), 1);
        }

        for (unsigned long n = 3; n < 9; n++) {
            // empty bipartite graph
            std::vector<std::vector<int>> zero(n, std::vector<int>(n, 0));
            BicliqueFinder finder_zero = BicliqueFinder(BipartiteGraph(zero));
            finder_zero.find_maximal_bicliques(algorithm);
            ASSERT_EQ(finder_zero.get_num_bicliques(), 1);

        }
    }
}

TEST(biclique_finder_test, to_string) {

    std::vector<std::vector<int>> mat =  J_minus_I(3);
    BicliqueFinder finder_J = BicliqueFinder(BipartiteGraph(mat));

    ASSERT_ANY_THROW(finder_J.to_string());
    finder_J.find_maximal_bicliques("improved");

    ASSERT_EQ(finder_J.to_string(), "2 3 | 4 \n3 | 4 5 \n2 | 4 6 \n1 3 | 5 \n1 | 5 6 \n1 2 | 6 \n");

}