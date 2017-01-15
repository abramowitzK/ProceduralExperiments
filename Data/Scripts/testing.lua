testing = { 
		value = 1000,
		}
function testing:update(dt)
    self.this.transform:rotate_x(self.value*dt)
end