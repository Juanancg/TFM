project('TFM_Planning_Algo','cpp', default_options: [])

target_name = 'PlanningAlgorithm'

inc = include_directories('src')

src_Components = files([
	'src/Components/Grid.cpp',
	'src/Components/xState.cpp',
	'src/Components/StateQueue.cpp'
])

src_Utils = files([
	'src/Utils/basic_functions.cpp'
])

src_Main = files([
	'src/main.cpp'
])

src = [
	src_Components,
	src_Utils,
	src_Main
]

executable(target_name, src, include_directories:inc)

gtest_dep = dependency('gtest', main: true, required: false)
src_unit_test = 'Unit_Test/tests.cpp'
if gtest_dep.found()
 	e = executable('test_'+target_name, src_unit_test, dependencies: gtest_dep, install : true, install_dir : 'bin_ut')
 	test('gtest ' + target_name, e)
endif
