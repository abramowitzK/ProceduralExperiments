testing = { 
		value = 1000,
		}
function testing:update(dt)
	if events.get_key_down(Keys.f) then
		self.this.transform:translate(0.0,0, 10.0*dt);
		print("Translating by:" );
		print(10.0*dt);
		print("\n")
	end
	if events.get_key_down(Keys.r) then
		self.this.transform:set_translation(Vector3:new(0,0,0));
		print("Resetting");
	end
end