class ::Module
  alias :_const_set_ :const_set

  def const_set n,q
    if q.is_a? Module
      this = self
      
      q.module_eval do
        singleton_class.define_method :inspect do
          this == ::Object ? "#{n}" : "#{this}::#{n}"
        end
      end      
    end
    
    _const_set_ n,q
  end
end
