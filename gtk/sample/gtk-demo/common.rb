# $Id: common.rb,v 1.3 2003/08/18 20:43:28 kzys Exp $
require 'gtk2'

module Demo
  def self.find_file(basename)
    %w(. /usr/share/gtk-2.0/demo).each do |dirname|
      path = File.join(dirname, basename)
      if File.exist?(path)
	return path
      end
    end
    raise Exception
  end

  class BasicWindow < Gtk::Window
    def initialize(title = nil)
      puts "#{self.class}#initialize"

      super(Gtk::Window::TOPLEVEL)
      if title
	set_title("#{title} in Ruby/GTK")
      end

      signal_connect("delete_event") do |widget, event|
	quit
      end
    end

    def quit
      destroy
      true
    end
  end
end
