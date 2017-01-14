testing = { 
		value = 1000,
		}
function testing:update(dt)
    self.owner.transform:rotate_x(self.value*dt)
end