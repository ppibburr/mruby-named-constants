mruby-named-constants
=====================

MRuby library that allows constants set via `const_set` to return name when `inspect` or `to_s` is called on them

```ruby
  ::Object.const_set :A, Class.new

  ::A.const_set :B, Class.new()
  ::A.const_set :C, Module.new()
  
  p ::A  # => A
  p A::B # => A::B
  p A::C # => A::C
```
