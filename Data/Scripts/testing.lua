testing = { 
		value = 1000,
		}
function testing:update(dt)
    self.owner.transform:rotate_y(self.value*dt)
end