testing = { 
		value = 100,
		test = 3,
		test9 = 3,
		test8 = 3,
		test7 = 3,
		test6 = 3,
		test5 = 3,
		test4 = 3,
		test3 = 3,
		test2 = 3,
		test1 = 3}
function testing:update(dt)
    self.owner.transform:rotate_y(self.value*dt)
end