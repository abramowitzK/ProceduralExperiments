function some_table:add_to_some_val(value)
    self.some_val = self.some_val + value
end

function print_some_val()
    print("some_table.some_val = " .. some_table.some_val)
end