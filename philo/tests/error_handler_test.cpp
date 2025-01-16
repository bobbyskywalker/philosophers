#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../inc/philo.h"
}

TEST(ErrorHandlerTest, ValidInput) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "5", "20000", "300000", "400000"};
    EXPECT_EQ(error_handler(5, args, philo), 0);
    free(philo);
}

TEST(ErrorHandlerTest, ValidInput2) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "5", "24957849", "32784", "474386", "32"};
    EXPECT_EQ(error_handler(6, args, philo), 0);
    free(philo);
}

TEST(ErrorHandlerTest, InvalidInputNegative) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "-1", "-20000", "-300000", "-400000", "jajko"};
    EXPECT_EQ(error_handler(6, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, NULL_ptr) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", NULL, "-20000", "-300000", "-400000"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, NULL_ptr2) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "7", "-20000", NULL, "-400000"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, NonNumeric) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "7", "-20000", "3982", "dummers"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, Overflows) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    char *args[] = {"philo", "36563453645326452364", "8563425823542874527453424", 
                          "275853246235425462354237452342", "368325854325482524584"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}
