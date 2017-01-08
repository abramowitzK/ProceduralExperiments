testing = { value = 10}
function testing:update(dt)
    self.owner.transform:rotate_y(self.value*dt)
    print(dt)
end