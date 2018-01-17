#include <memory>
#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

namespace ext = snsinfu::ext;

TEST_CASE("using array_view in a virtual interface")
{
    class reducer
    {
      public:
        virtual ~reducer() = default;
        virtual double reduce(ext::array_view<double const> nums) const = 0;
    };

    class summing_reducer : public reducer
    {
      public:
        double reduce(ext::array_view<double const> nums) const override
        {
            double sum = 0;
            for (auto n : nums) {
                sum += n;
            }
            return sum;
        }
    };

    std::unique_ptr<reducer> rd{new summing_reducer{}};

    std::vector<double> vector = {1.0, 2.0, 3.0};
    double array[] = {4.0, 5.0, 6.0};

    CHECK(rd->reduce(ext::view(vector)) == 6.0);
    CHECK(rd->reduce(ext::view(array)) == 15.0);
}
