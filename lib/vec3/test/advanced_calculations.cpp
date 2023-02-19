#include <gtest/gtest.h>

using namespace std;

extern "C" {
	#include <vec3.h>
}

TEST(libvec3, dot)
{
	t_vec3 vec1, vec2;
	double res_test, res_vec;

	vec1 = vec3_new(-242, 0 , 4.5131);
	vec2 = vec3_new(242, 0.4241213, -0.01);
	res_vec = vec3_dot(&vec1, &vec2);
	res_test = 0;
	for (uint8_t i = 0; i < 3; i++)
		res_test += vec1.data[i] * vec2.data[i];
	EXPECT_DOUBLE_EQ(res_vec, res_test);

	vec1 = vec3_new(5232424.131331313, -0.3131313 , 4.5131);
	vec2 = vec3_new(242, 0.4241213, 0);
	res_vec = vec3_dot(&vec1, &vec2);
	res_test = 0;
	for (uint8_t i = 0; i < 3; i++)
		res_test += vec1.data[i] * vec2.data[i];
	EXPECT_DOUBLE_EQ(res_vec, res_test);
}

TEST(libvec3, cross)
{
	t_vec3 vec1, vec2, vec_res;
	double test_res[3];

	vec1 = vec3_new(-242, 0 , 4.5131);
	vec2 = vec3_new(242, 0.4241213, -0.01);
	vec_res = vec3_cross(&vec1, &vec2);
	
	test_res[0] = vec1.data[1] * vec2.data[2] - vec1.data[2] * vec2.data[1];
	test_res[1] = vec1.data[2] * vec2.data[0] - vec1.data[0] * vec2.data[2];
	test_res[2] = vec1.data[0] * vec2.data[1] - vec1.data[1] * vec2.data[0];

	for (uint8_t i = 0; i < 3; i++)
		EXPECT_DOUBLE_EQ(vec_res.data[i], test_res[i]);	

	vec1 = vec3_new(524.4231, 0 , 0);
	vec2 = vec3_new(242.44, 52424, -0.01);
	vec_res = vec3_cross(&vec1, &vec2);
	
	test_res[0] = vec1.data[1] * vec2.data[2] - vec1.data[2] * vec2.data[1];
	test_res[1] = vec1.data[2] * vec2.data[0] - vec1.data[0] * vec2.data[2];
	test_res[2] = vec1.data[0] * vec2.data[1] - vec1.data[1] * vec2.data[0];

	for (uint8_t i = 0; i < 3; i++)
		EXPECT_DOUBLE_EQ(vec_res.data[i], test_res[i]);	
}
