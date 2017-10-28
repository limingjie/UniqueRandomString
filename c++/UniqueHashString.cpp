#include <iostream>
#include <unordered_map>

std::string randomBase64 = "Nz746LU-BCcolIygTV9Z0GaeX8puRKO5PEisvWDt3qbnrdFhf1wAMkHxQ_2jYmSJ";

// Some more random base64 strings
//     "jt1vZpX9Fi6qHnRhrTb3-UuakzK0_JEW47wxeCO8Qf5IlgPsoYScDm2yNLdGAMBV";
//     "PGpN7Ws0gaFR6mvJT1UXl3bHBxtnuiyq-d9fj_wYckV2zSKIoA5rLMOeDC4ZhEQ8";
//     "3mqEds5hZkUyjD269ABplRHgI8iYzr-XOLbwF07ctou1SveV4KGQCMPNaxnTWfJ_";
//     "b9Tm5k27HuB-VyLEl13RIMwSKNGUDYQpnPhsJgavc6OiC4ofjFrAxd0_ztZqWX8e";
//     "Na3gFiQx1sS8LKyOuZrYBpjzwGEDPbomdq654RcIX_0e2C7k-WHnUhVAJlMf9Ttv";
//     "Zw84hDk-pN5uKcPy1_LdqIn0tQCJWBAROm26XSijzegxME7FHVbUaTGlorf3sYv9";
//     "fBe04QGcSkXsLud76gbxIFpOyUHajWiZmYMrEnDhtw5KqCRA8v3lPTz_o12VN9-J";
//     "RoFTY_jOZtbkai8651lp-VqzEgd4rLuDJ2WHBUv3xA9C0m7wKnsPhfMSQecGINXy";
//     "r3fi0dH_6kYyOaQ8s2eUBWucGS7PnNq9moFbTEh4C1xwMXJzIv-VZDljtRgLA5pK";
//     "vjOShxu1Cq8-JBsylNTGoiX5Kpt0cAEZr9VP2HMw3mkzFI4YL_bfRUegDWn7Qa6d";

std::unordered_map<char, unsigned int> unRandomBase64;

std::string encode(uint64_t value)
{
    std::string code;
    code.reserve(11);
    uint64_t accumulate = 0, remainder = 0, position;

    do
    {
        accumulate += remainder;
        remainder = value & 0x3f;
        value >>= 6;
        position = (accumulate + remainder) & 0x3f;
        code.push_back(randomBase64[position]);
    } while (value > 0);

    return code;
}

uint64_t decode(std::string &code)
{
    uint64_t value = 0, accumulate = 0, remainder, position;

    size_t size = code.size();
    for (size_t i = 0; i < size; i++)
    {
        position = unRandomBase64[code[i]];
        remainder = (position + 64 - accumulate) & 0x3f;
        accumulate += remainder;
        value += remainder << (6 * i);
    }

    return value;
}

int main()
{
    for (int i = 0; i < 64; i++)
    {
        unRandomBase64[randomBase64[i]] = i;
    }

    // std::cout << "Value -> encode() -> decode()" << std::endl;

    int count = 0;
    for (uint64_t i = 16345678912345678900ull; i < 16345678912345678900ull + 65536000ull; i++)
    {
        std::string code = encode(i);
        uint64_t value = decode(code);
        // std::cout << i << " -> "<< code << " -> " << value << std::endl;

        if (i != value)
        {
            count++;
        }

        if (i % 65536 == 0)
        {
            std::cout << '.';
        }
    }

    std::cout << "Decode Error Count = " << count << std::endl;

    return 0;
}