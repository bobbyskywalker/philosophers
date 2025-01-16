#include <gtest/gtest.h>
#include <cstddef>
#include <stdlib.h>

extern "C" {
    #include "../src/error_handler.c"
    #include "../src/utils.c"
}

TEST(ErrorHandlerTest, ValidInput) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    const char *args[] = {"5", "20000", "300000", "400000"};
    EXPECT_EQ(error_handler(5, args, philo), 0);
    free(philo);
}

TEST(ErrorHandlerTest, ValidInput2) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    const char *args[] = {"5", "24957849", "32784", "474386", "32"};
    EXPECT_EQ(error_handler(6, args, philo), 0);
    free(philo);
}

TEST(ErrorHandlerTest, InvalidInputNegative) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    const char *args[] = {"-1", "-20000", "-300000", "-400000", "44"};
    EXPECT_EQ(error_handler(6, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, NULL_ptr) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    const char *args[] = {NULL, "-20000", "-300000", "-400000"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}

TEST(ErrorHandlerTest, Overflows) {
    t_philo *philo = (t_philo *)malloc(sizeof(t_philo));
    const char *args[] = {"36563453645326452364", "8563425823542874527453424", 
                          "275853246235425462354237452342", "368325854325482524584"};
    EXPECT_EQ(error_handler(5, args, philo), 1);
    free(philo);
}
